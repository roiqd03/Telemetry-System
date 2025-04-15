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
class ITrackerAsset;

class Tracker
{
private:
	Tracker() {};
	bool init(const std::string& gameID);
	void end();
	
	Persistence* _persistence;
	// A priori diria que esto no es necesario
	std::list<ITrackerAsset*> _activeTrackers;

	std::string _gameID;
	std::string _playerID;
	std::string _sessionID;
	const std::chrono::system_clock::time_point p1 = std::chrono::system_clock::now();

	static Tracker* _instance;
public:
	void TrackEvent(TrackerEvent* trackerEvent);
	
	static bool Init(const std::string& gameID);
	static void End();
	static Tracker* Instance();
};

