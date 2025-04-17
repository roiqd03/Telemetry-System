#pragma once
#include "TrackerEvent.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class Persistence
{
public:
	Persistence();
	void QueueEvent(const TrackerEvent& trackerEvent);
	void ForceFlush(); //Para forzar un flush en momentos concretos
protected:
	const std::string SuddentSerialization(); //Serializa de golpe todos los eventos
	virtual void Flush() = 0;
	std::queue<TrackerEvent> eventsQueue;
	uint32_t numBeforeFlush = 100; // El número de eventos encolados antes de hacer el flush
private:
	mutable std::mutex mutex;
	std::condition_variable mutexCondition;
};

