#pragma once
#include "ITrackerAsset.h"

class DefaultTrackerAsset : public ITrackerAsset
{
public:
	~DefaultTrackerAsset() = default;
	bool accept(TrackerEvent* trackerEvent) override;
	bool process(Persistence* persistence, TrackerEvent* trackerEvent) override;
};

