#include "Tracker.h"

int main() {
	if (!Tracker::Init("Damn")) {
		return -1;
	}

	Tracker::End();
	return 0;
}