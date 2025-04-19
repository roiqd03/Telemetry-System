#pragma once
#include <string>
#include "FilePersistence.h"
#include "Persistence.h"
#include <type_traits>

/// @brief Interfaz que deben definir todos los serializadores en el formato que se quieran crear.
/// Define metodos para serializar todos los tipos de variables necesarias.
/// Lo que ISerializer espera de las clases que hereden es que funcionen a modo de "tabla" de la siguiente manera:
class ISerializer {
	friend class FilePersistence;
	friend class Persistence;
public:

	/// @brief Permite la serializacion de cualquier tipo de variable basica.
	/// @tparam T Cualquier clase basica de C++
	/// @param value Valor a serializar
	/// @param name Nombre de la variable
	template <class T, std::convertible_to<std::string> S> 
	requires std::is_arithmetic_v<std::remove_cvref_t<T>> || std::is_same_v<std::remove_cvref_t<T>, std::string>
	void serialize(T&& value, S&& name) {
		serialize_impl(std::forward<T>(value), std::forward<S>(name));
	}

	/// @brief Genera una "tabla" dentro de la "tabla" actual.
	/// @param name Nombre de la "tabla"
	virtual void openObject(const std::string& name) = 0;

	/// @brief Cierra la ultima "tabla" abierta.
	virtual void closeObject() = 0;
protected:
	/// @brief Inicializa el serializador
	virtual const std::string init() = 0;

	/// @brief Inicializa un evento
	virtual void openEvent() = 0;

	/// @brief Vierte todo el contenido de la "tabla" a una cadena de texto
	/// @return Cadena de texto con todo el contenido de la tabla
	virtual const std::string dump() = 0;

	/// @brief Libera el serializador
	virtual const std::string release() = 0;

	/// @brief Permite la serializacion de enteros
	/// @param number Entero
	/// @param name Nombre de la variable.
	virtual void serialize_impl(int number, const std::string& name) = 0;

	/// @brief Permite la serializacion de enteros de hasta 64 bits
	/// @param number Entero de hasta 64 bits
	/// @param name Nombre de la variable.
	virtual void serialize_impl(int64_t number, const std::string& name) = 0;

	/// @brief Permite la serializacion de numeros con punto flotante de hasta 32 bits.
	/// @param number Numero en punto flotante de hasta 32 bits.
	/// @param name Nombre de la variable.
	virtual void serialize_impl(float number, const std::string& name) = 0;

	/// @brief Permite la serializacion de numeros con punto flotante de hasta 64 bits.
	/// @param number Numero en punto flotante de hasta 64 bits.
	/// @param name Nombre de la variable.
	virtual void serialize_impl(double number, const std::string& name) = 0;

	/// @brief Permite la serializacion de booleanos.
	/// @param value Booleano.
	/// @param name Nombre de la variable.
	virtual void serialize_impl(bool value, const std::string& name) = 0;

	/// @brief Permite la serializacion de caracteres.
	/// @param value Caracter.
	/// @param name Nombre de la variable.
	virtual void serialize_impl(char value, const std::string& name) = 0;

	/// @brief Permite la serializacion de cadenas de texto.
	/// @param value Cadena de texto.
	/// @param name Nombre de la variable.
	virtual void serialize_impl(const std::string& value, const std::string& name) = 0;
};

