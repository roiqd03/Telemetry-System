#pragma once
class TrackerEvent;
class Persistence;

class ITrackerAsset
{
public:
	ITrackerAsset() = default;
	virtual ~ITrackerAsset() = default;
	virtual bool accept(TrackerEvent* trackerEvent) = 0;
	// Debe devolver True si el evento se ha metido en la cola de Persistence
	virtual bool process(Persistence* persistence, TrackerEvent* trackerEvent) = 0;
};

