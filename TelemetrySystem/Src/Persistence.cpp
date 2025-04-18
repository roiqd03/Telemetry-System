#include "Persistence.h"
#include "ISerializer.h"
#include "Serializers/JSONSerializer.h"

Persistence::Persistence() : eventsQueue(), mutex(), mutexCondition()
{
	_serializer = new JSONSerializer();
	_serializer->init(nullptr);
}

Persistence::~Persistence() {
	_serializer->release();
	delete _serializer;
	_serializer = nullptr;
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

const std::string Persistence::SuddenSerialization()
{
	int total = eventsQueue.size();
	for (int i = 0; i < total; ++i) {
		_serializer->openEvent();
		eventsQueue.front().serialize(_serializer);
		eventsQueue.pop();
	}
	return _serializer->dump();
}
