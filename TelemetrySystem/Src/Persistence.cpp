#include "Persistence.h"


Persistence::Persistence() : eventsQueue(), mutex(), mutexCondition()
{
}

void Persistence::QueueEvent(const TrackerEvent& trackerEvent)
{
	std::lock_guard<std::mutex> lock(mutex);
	eventsQueue.push(trackerEvent);
	if (eventsQueue.size() >= numBeforeFlush) {
		Flush();
	}
	mutexCondition.notify_one();
}

void Persistence::ForceFlush()
{
	if (eventsQueue.empty()) return;
	std::lock_guard<std::mutex> lock(mutex);
	Flush();
	mutexCondition.notify_one();

}

const std::string Persistence::SuddentSerialization()
{
	//TODO imagino que habría que tener un objeto de tipo "Serializer" con el que serializar toda la información
	return std::string();
}
