#include "TrackerEvent.h"

TrackerEvent::TrackerEvent(const std::string& eventType)
{
}

TrackerEvent::~TrackerEvent()
{
}

const std::string TrackerEvent::ToCSV()
{
	return std::string();
}

const std::string TrackerEvent::ToJson()
{
	return std::string();
}

void TrackerEvent::SetCommonProperties(int timestamp, const std::string& gameID, const std::string& playerID, const std::string& sessionID)
{
	this->timestamp = timestamp;
	this->gameID = gameID;
	this->playerID = playerID;
	this->sessionID = sessionID;
}
