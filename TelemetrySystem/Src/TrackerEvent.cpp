#include "TrackerEvent.h"
#include "ISerializer.h"

TrackerEvent::TrackerEvent(const std::string& eventType)
{
}

TrackerEvent::~TrackerEvent()
{
}

const std::string serialize(ISerializer* serializer) {

}

void TrackerEvent::SetCommonProperties(int timestamp, const std::string& gameID, const std::string& playerID, const std::string& sessionID)
{
	this->timestamp = timestamp;
	this->gameID = gameID;
	this->playerID = playerID;
	this->sessionID = sessionID;
}
