#pragma once
#include "TrackerEvent.h"
#include "CircularQueue.h"
#include <queue>

class ISerializer;

class Persistence
{
public:
	Persistence();
	virtual ~Persistence();
	void QueueEvent(TrackerEvent* trackerEvent);
	void ForceFlush(); //Para forzar un flush en momentos concretos
	void SetSerializer(ISerializer* serializer);
	ISerializer* GetSerializer();
	virtual void Release() = 0;
protected:
	const std::string SuddenSerialization(); //Serializa de golpe todos los eventos
	virtual void Flush() = 0;
	circular_buffer<TrackerEvent*>* eventsQueue;
	uint32_t numBeforeFlush = 100; // El número de eventos encolados antes de hacer el flush
	ISerializer* _serializer = nullptr;
};

