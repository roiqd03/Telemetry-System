#include "DefaultTrackerAsset.h"
#include "TrackerEvent.h"
#include "Tracker.h"
#include "Persistence.h"

bool DefaultTrackerAsset::accept(TrackerEvent* trackerEvent)
{
    std::string s = trackerEvent->GetEventType();
    return s == "GameStart" || s == "GameEnd";
}

bool DefaultTrackerAsset::process(Persistence* persistence, TrackerEvent* trackerEvent)
{
    persistence->QueueEvent(trackerEvent);
    persistence->ForceFlush();
    return true;
}
