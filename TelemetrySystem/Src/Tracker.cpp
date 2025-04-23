#include "Tracker.h"
#include "TrackerEvent.h"
#include "FilePersistence.h"
#include "ServerPersistence.h"
#include "ITrackerAsset.h"
#include "TrackerAssets/DefaultTrackerAsset.h"
#include "Serializers/JSONSerializer.h"
#include "Serializers/CSVSerializer.h"

Tracker* Tracker::_instance = nullptr;

InitValues Tracker::init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType)
{
	// settear variables
	_gameID = gameID;
	

	// obtener numero de serie
	FILE* systemCall = _popen("wmic baseboard get serialnumber", "r");
	if (!systemCall) return { false, nullptr, nullptr };
	
	char playerID[PLAYER_ID_LENGTH];

	fgets(playerID, PLAYER_ID_LENGTH, systemCall); // linea no relevante
	fgets(playerID, PLAYER_ID_LENGTH, systemCall); // numero de serie
	bool found = false;
	for (int i = 0; i < PLAYER_ID_LENGTH && !found; ++i) {
		if (playerID[i] == ' ') {
			found = true;
			playerID[i] = '\0';
		}
	}

	_pclose(systemCall);

	std::string initialTimestamp = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
		p1.time_since_epoch()).count());

	// setteamos el resto de variables con la informacion anterior
	_playerID = std::string(playerID);
	_sessionID = _playerID;
	_sessionID.append(initialTimestamp);


	// crear objeto de persistencia
	if (!createPersistence(persistenceType)) 		
		return { false, nullptr, nullptr };

	if (!createSerializer(serializerType))
		return { false, nullptr, nullptr };

	_activeTrackers.push_back(new DefaultTrackerAsset());

	// crear primer evento de inicio de juego y persistirlo
	return { true, _persistence, _persistence->GetSerializer() };
}

void Tracker::end()
{
	TrackEvent(new TrackerEvent(END_EVENT_NAME));

	if (_persistence != nullptr)
		_persistence->Release();
		delete _persistence;
	
	for (auto trackerAsset = _activeTrackers.begin(); trackerAsset != _activeTrackers.end(); ++trackerAsset) {
		delete (*trackerAsset);
	}
	_activeTrackers.clear();
}

bool Tracker::createPersistence(PersistenceTypes type)
{
	switch (type)
	{
	case Tracker::P_FILE:
		_persistence = new FilePersistence();
		break;
	/*case Tracker::P_SERVER:
		_persistence = new ServerPersistence();
		break;*/
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
	else ret = { false, nullptr, nullptr };
	
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

	bool validEvent = false;
	for (auto trackerAsset : _activeTrackers) {
		if (trackerAsset->accept(trackerEvent)) {
			validEvent = true;
			if (!trackerAsset->process(_persistence, trackerEvent)) {
				End();
				return;
			}
		}
	}

	if (!validEvent)
		delete trackerEvent;

	_persistence->DeleteEvents();
}

void Tracker::AddTrackerAsset(ITrackerAsset* trackerAsset)
{
	_activeTrackers.push_back(trackerAsset);
}

void Tracker::Start()
{
	TrackEvent(new TrackerEvent(START_EVENT_NAME));
}
