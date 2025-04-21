#pragma once

#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <chrono>

#define PLAYER_ID_LENGTH 64

class TrackerEvent;
class Persistence;
class ISerializer;
class ITrackerAsset;

struct InitValues {
	bool couldInitialize;
	Persistence* persistence;
	ISerializer* serializer;
};

class Tracker
{
public:
	enum PersistenceTypes { P_FILE, P_SERVER };
	enum SerializerTypes { S_JSON, S_CSV };

	void TrackEvent(TrackerEvent* trackerEvent);
	void Flush();

	static InitValues Init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType);
	static void End();
	static Tracker* Instance();
	
private:
	Tracker() {};
	InitValues init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType);
	void end();
	bool createPersistence(PersistenceTypes type);
	bool createSerializer(SerializerTypes type);

	Persistence* _persistence;
	// A priori diria que esto no es necesario
	std::list<ITrackerAsset*> _activeTrackers;

	std::string _gameID;
	std::string _playerID;
	std::string _sessionID;
	const std::chrono::system_clock::time_point p1 = std::chrono::system_clock::now();


	static Tracker* _instance;
};

