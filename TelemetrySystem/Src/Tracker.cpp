#include "Tracker.h"
#include "TrackerEvent.h"
#include "FilePersistence.h"
#include "ServerPersistence.h"
#include "Serializers/JSONSerializer.h"
#include "Serializers/CSVSerializer.h"

Tracker* Tracker::_instance = nullptr;

InitValues Tracker::init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType)
{
	// settear variables
	_gameID = gameID;
	

	// obtener numero de serie
	system("wmic bios get serialnumber > sn.txt");
	wchar_t playerID[PLAYER_ID_LENGTH];

	FILE* fp = nullptr;
	if (fopen_s(&fp, "sn.txt", "r, ccs=UTF-8") != 0) {
		remove("sn.txt");
		return {false, nullptr, nullptr};
	}
	fgetws(playerID, PLAYER_ID_LENGTH, fp); // linea no relevante
	fgetws(playerID, PLAYER_ID_LENGTH, fp); // numero de serie

	// Antes de cerrar, compruebo si hubo algun error
	if (ferror(fp) != 0) {
		fclose(fp);
		remove("sn.txt");
		return { false, nullptr, nullptr };
	}
	
	fclose(fp);          
	// borramos el archivo
	remove("sn.txt");

	std::string initialTimestamp = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
		p1.time_since_epoch()).count());

	// setteamos el resto de variables con la informacion anterior
	std::wstring player(playerID);
	_playerID = std::string(player.begin(), player.end());
	_sessionID = _playerID;
	_sessionID.append(initialTimestamp);


	// crear objeto de persistencia
	if (!createPersistence(persistenceType)) 		
		return { false, nullptr, nullptr };

	if (!createSerializer(serializerType))
		return { false, nullptr, nullptr };


	// crear primer evento de inicio de juego y persistirlo
	return { true, _persistence, _persistence->GetSerializer() };
}

void Tracker::end()
{
	if (_persistence != nullptr)
		_persistence->Release();
		delete _persistence;
}

bool Tracker::createPersistence(PersistenceTypes type)
{
	switch (type)
	{
	case Tracker::P_FILE:
		_persistence = new FilePersistence();
		break;
	case Tracker::P_SERVER:
		_persistence = new ServerPersistence();
		break;
	default:
		return false;
	}
	return true;
}

bool Tracker::createSerializer(SerializerTypes type)
{
	ISerializer* serializer;
	switch (type)
	{
	case Tracker::S_JSON:
		serializer = new JSONSerializer();
		break;
	case Tracker::S_CSV:
		serializer = new CSVSerializer();
		break;
	default:
		return false;
		break;
	}
	_persistence->SetSerializer(serializer);
	return true;
}

InitValues Tracker::Init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType)
{
	InitValues ret;
	if (_instance == nullptr) {
		_instance = new Tracker();
		ret = _instance->init(gameID, persistenceType, serializerType);
		if (!ret.couldInitialize) {
			_instance->end();
			delete _instance;
			_instance = nullptr;
		}
	}
	return ret;
}

void Tracker::End()
{
	if (_instance != nullptr) {
		_instance->end();
		delete _instance;
		_instance = nullptr;
	}
}

Tracker* Tracker::Instance()
{
	return _instance;
}

void Tracker::TrackEvent(TrackerEvent* trackerEvent)
{
	trackerEvent->SetCommonProperties(std::chrono::duration_cast<std::chrono::milliseconds>(
		p1.time_since_epoch()).count(), _gameID, _playerID, _sessionID);
	if (_persistence) _persistence->QueueEvent(*trackerEvent);
}
