#pragma once
#include "TrackerEvent.h"
#include <queue>

class Persistence
{
public:
	void QueueEvent(const TrackerEvent& trackerEvent);
	virtual void Flush() = 0;
protected:
	std::queue<TrackerEvent> queueEvents; // Por implementar
};

