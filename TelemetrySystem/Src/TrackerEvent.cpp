#include "TrackerEvent.h"
#include "ISerializer.h"

TrackerEvent::TrackerEvent(const std::string& eventType)
{
	this->eventType = eventType;
}

TrackerEvent::~TrackerEvent()
{
}

void TrackerEvent::serialize(ISerializer* serializer) {
	serializer->serialize(timestamp, "timestamp");
	serializer->serialize(gameID, "gameID");
	serializer->serialize(playerID, "playerID");
	serializer->serialize(sessionID, "sessionID");
	serializer->serialize(eventType, "eventType");
}

void TrackerEvent::SetCommonProperties(long long timestamp, const std::string& gameID, const std::string& playerID, const std::string& sessionID)
{
	this->timestamp = timestamp;
	this->gameID = gameID;
	this->playerID = playerID;
	this->sessionID = sessionID;
}
