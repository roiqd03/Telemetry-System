#pragma once
#include "TrackerEvent.h"

class ISerializer
{
public:
	virtual const std::string Serialize(const TrackerEvent& trackerEvent) = 0;
};

