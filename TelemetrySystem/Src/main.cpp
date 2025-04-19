#include "Tracker.h"
#include "FilePersistence.h"
#include "ServerPersistence.h"
#include "Serializers/JSONSerializer.h"

int main() {
	InitValues ret = Tracker::Init("Damn", Tracker::PersistenceTypes::P_FILE, Tracker::SerializerTypes::S_JSON);
	if (!ret.couldInitialize) {
		return -1;
	}
	
	// esto solo seria la primera vez para inicializarlo con la clase que queramos, luego se usa todo mediante
	// las interfaces que tiene el tracker
	static_cast<JSONSerializer*>(ret.serializer)->init(nullptr);
	static_cast<FilePersistence*>(ret.persistence)->Init("test.json");
	//static_cast<ServerPersistence*>(ret.persistence)->Init("127.0.0.1", "8080");


	Tracker::End();
	return 0;
}