#pragma once
#include "TrackerEvent.h"
#include <cstdint>

/// @brief Interfaz que deben definir todos los serializadores en el formato que se quieran crear.
/// Define metodos para serializar todos los tipos de variables necesarias.
class ISerializer {
public:
#pragma region integers
	/// @brief Permite la serializacion de enteros de 8 bits o char con signo.
	/// @param number Numero de 8 bits o char con signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeInt8(int8_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 8 bits o char sin signo.
	/// @param number Numero de 8 bits o char sin signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeUint8(uint8_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 16 bits o short con signo.
	/// @param number Numero de 16 bits o short con signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeInt16(int16_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 16 bits o short sin signo.
	/// @param number Numero de 16 bits o short sin signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeUint16(uint16_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 32 bits o int con signo.
	/// @param number Numero de 32 bits o int con signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeInt32(int32_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 32 bits o int sin signo.
	/// @param number Numero de 32 bits o int sin signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeUint32(uint32_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 64 bits o long long con signo.
	/// @param number Numero de 64 bits o long long con signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeInt64(int64_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de 64 bits o long long sin signo.
	/// @param number Numero de 64 bits o long long sin signo.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeUint64(uint64_t number, const std::string& name) = 0;
#pragma endregion

#pragma region floatingpoint
	/// @brief Permite la serializacion de numeros con punto flotante de hasta 32 bits.
	/// @param number Numero en punto flotante de hasta 32 bits.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeFloat(float number, const std::string& name) = 0;

	/// @brief Permite la serializacion de numeros con punto flotante de hasta 64 bits.
	/// @param number Numero en punto flotante de hasta 64 bits.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeDouble(double number, const std::string& name) = 0;
#pragma endregion

	/// @brief Permite la serializacion de booleanos.
	/// @param value Booleano.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeBool(bool value, const std::string& name) = 0;

	/// @brief Permite la serializacion de cadenas de texto.
	/// @param value Cadena de texto.
	/// @param name Nombre de la variable.
	/// @return Cadena de texto con la variable serializada.
	virtual const std::string serializeString(const std::string& value, const std::string& name) = 0;
};

