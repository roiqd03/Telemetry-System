#pragma once
#pragma once
#include <string>

class TrackerEvent
{
public:
	TrackerEvent(const std::string& eventType);
	~TrackerEvent();
	virtual const std::string ToCSV();
	virtual const std::string ToJson();
	void SetCommonProperties(int timestamp, const std::string& gameID, const std::string& playerID, const std::string& sessionID);
protected:
	std::string eventType;

	int timestamp;
	std::string gameID;
	std::string playerID;
	std::string sessionID;
};

