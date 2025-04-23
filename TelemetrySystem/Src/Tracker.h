#pragma once

#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#define PLAYER_ID_LENGTH 64
#define START_EVENT_NAME "GameStart"
#define END_EVENT_NAME "GameEnd"

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
	enum PersistenceTypes { P_FILE };
	enum SerializerTypes { S_JSON, S_CSV };

	void TrackEvent(TrackerEvent* trackerEvent);
	void AddTrackerAsset(ITrackerAsset* trackerAsset);
	void Start();

	static InitValues Init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType);
	static void End();
	static Tracker* Instance();
	
private:
	Tracker() = default;
	~Tracker() = default;
	InitValues init(const std::string& gameID, PersistenceTypes persistenceType, SerializerTypes serializerType);
	void end();
	bool createPersistence(PersistenceTypes type);
	bool createSerializer(SerializerTypes type);

	Persistence* _persistence = nullptr;
	std::list<ITrackerAsset*> _activeTrackers;

	std::string _gameID;
	std::string _playerID;
	std::string _sessionID;
	const std::chrono::system_clock::time_point p1 = std::chrono::system_clock::now();


	static Tracker* _instance;
};

