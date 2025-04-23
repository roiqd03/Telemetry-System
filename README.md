# Telemetry-System
## Example
### Initialization with FilePersistence and JSONSerializer
```
InitValues init = Tracker::Init("Damn", Tracker::P_FILE, Tracker::S_JSON);
if (init.couldInitialize) { // if it could not initialize, it is auto deleted
	init.serializer->init(nullptr); // initialize serializer with its parameters

	const std::string baseDir = "../analysis/data";

	const std::string sessionId = Tracker::Instance()->GetSessionID();
	std::string filename = baseDir + "/telemetry_" + sessionId;

	bool canInitialize = static_cast<FilePersistence*>(init.persistence)->Init(filename); // initialize persistence with its parameters

	if (canInitialize) { // if persistence is initialize, you should create the tracker assets
        	// Tracker assets to accept events and queue events. DefaultTrackerAsset.h and .cpp is an example, used in order to accept GameStart and GameEnd events.
		ProgressionTracker* progressionTracker = new ProgressionTracker();
		Tracker::Instance()->AddTrackerAsset(progressionTracker);

		GameEventTracker* gameTracker = new GameEventTracker();
		Tracker::Instance()->AddTrackerAsset(gameTracker);

        	// starts the tracker with the event GameStart
		Tracker::Instance()->Start();
	}
	else { // if persistence could not initialize, then delete the tracker
		Tracker::End();
	}
}
```

### During the game

```
if(Tracker::Instance()){
    	LevelStartEvent* levelStart = new LevelStartEvent(_currentMap);
	Tracker::Instance()->TrackEvent(levelStart);
}
```

### At the end of the game

```
Tracker::End();
```
