#include "Persistence.h"
#include "ISerializer.h"
#include "Serializers/JSONSerializer.h"
#include "Serializers/CSVSerializer.h"

Persistence::Persistence() : eventsQueue()
{
	//_serializer = new JSONSerializer(nullptr);
	//_serializer = new CSVSerializer(nullptr, /*numero de elementos totales de la cabecera*/);
	eventsQueue = new circular_buffer<TrackerEvent*>(numBeforeFlush);
}

Persistence::~Persistence() {
	delete _serializer;
	_serializer = nullptr;
	delete eventsQueue;
}

void Persistence::QueueEvent(TrackerEvent* trackerEvent)
{
	if(eventsQueue->size() == 0 || (eventsQueue->size() > 0 && eventsQueue->front() != trackerEvent)) eventsQueue->push(trackerEvent);
	if (eventsQueue->full()) {
		Flush();
	}
}

void Persistence::ForceFlush()
{
	if (eventsQueue->empty()) return;
	Flush();
}

void Persistence::SetSerializer(ISerializer* serializer)
{
	_serializer = serializer;
}

ISerializer* Persistence::GetSerializer()
{
	return _serializer;
}

void Persistence::DeleteEvents()
{
	for (auto elem = _eventsToDelete.begin(); elem != _eventsToDelete.end(); ++elem) {
		delete (*elem);
	}

	_eventsToDelete.clear();
}

const std::string Persistence::SuddenSerialization()
{
	int total = eventsQueue->size();
	for (int i = 0; i < total; ++i) {
		_serializer->openEvent();
		eventsQueue->front()->serialize(_serializer);
		_eventsToDelete.insert(eventsQueue->front());
		eventsQueue->pop();
	}
	return _serializer->dump();
}
