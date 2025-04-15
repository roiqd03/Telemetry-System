#include "Tracker.h"
#include "TrackerEvent.h"
#include "Persistence.h"

Tracker* Tracker::_instance = nullptr;

bool Tracker::init(const std::string& gameID)
{
	// settear variables
	_gameID = gameID;
	

	// obtener numero de serie
	system("wmic bios get serialnumber > sn.txt");
	wchar_t playerID[PLAYER_ID_LENGTH];

	FILE* fp = nullptr;
	if (fopen_s(&fp, "sn.txt", "r, ccs=UTF-8") != 0) {
		remove("sn.txt");
		return false;
	}
	fgetws(playerID, PLAYER_ID_LENGTH, fp); // linea no relevante
	fgetws(playerID, PLAYER_ID_LENGTH, fp); // numero de serie

	// Antes de cerrar, compruebo si hubo algun error
	if (ferror(fp) != 0) {
		fclose(fp);
		remove("sn.txt");
		return false;
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

	// crear primer evento de inicio de juego y persistirlo
	return true;
}

void Tracker::end()
{
}

bool Tracker::Init(const std::string& gameID)
{
	if (_instance == nullptr) {
		_instance = new Tracker();
		if (!_instance->init(gameID)) {
			_instance->end();
			delete _instance;
			_instance = nullptr;
			return false;
		}
	}
	return true;
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
