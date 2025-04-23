#pragma once
#include "TrackerEvent.h"
#include "CircularQueue.h"
#include <queue>
#include <unordered_set>

class ISerializer;

class Persistence
{
public:
	Persistence();
	virtual ~Persistence();
	bool QueueEvent(TrackerEvent* trackerEvent);
	bool ForceFlush(); //Para forzar un flush en momentos concretos
	void SetSerializer(ISerializer* serializer);
	ISerializer* GetSerializer();
	virtual void Release() = 0;
	void DeleteEvents();
	inline bool IsInitialized() { return _initialized; }
protected:
	const std::string SuddenSerialization(); //Serializa de golpe todos los eventos
	virtual bool Flush() = 0;
	circular_buffer<TrackerEvent*>* eventsQueue;
	uint32_t numBeforeFlush = 100; // El número de eventos encolados antes de hacer el flush
	ISerializer* _serializer = nullptr;
	std::unordered_set<TrackerEvent*> _eventsToDelete;
	bool _initialized = false;
};

