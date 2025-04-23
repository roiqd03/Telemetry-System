#pragma once
#include <string>

class ISerializer;

class TrackerEvent
{
public:
	TrackerEvent(const std::string& eventType);

	virtual ~TrackerEvent();

	/// @brief Llamada para la serializacion de un evento.
	/// En el caso de los eventos que hereden de TrackerEvent, es necesario sobreescribir el metodo llamando a las funciones propias del serializador con los atributos que se quieran serializar, sin olvidar
	/// primero una llamada a TrackerEvent::serialize() para serializar los atributos comunes.
	/// @param serializer Serializador que se vaya a usar.
	virtual void serialize(ISerializer* serializer);

	inline const std::string GetEventType() { return eventType; }

	void SetCommonProperties(long long timestamp, const std::string& gameID, const std::string& playerID, const std::string& sessionID);
protected:
	std::string eventType;

	long long timestamp;
	std::string gameID;
	std::string playerID;
	std::string sessionID;
};

