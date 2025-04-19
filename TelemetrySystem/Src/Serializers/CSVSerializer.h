#ifndef UAJ2425_G05_CSVSERIALIZER_H
#define UAJ2425_G05_CSVSERIALIZER_H

#include "../ISerializer.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>
#include <any>

/// @brief El serializador de CSV es mas complejo que el de JSON porque necesitamos convertir tipos complejos a campos sencillos.
/// Con CSV tenemos el siguiente problema: si al principio tengo datos que solo me han producido 10 variables de cabecera, los he dumpeado a un archivo, y posteriormente se han
/// llamado nuevos eventos que tienen distintas variables de cabecera, tendre en un mismo CSV lineas con 10 variables (las del primer dump), y el resto, que tendran mas variables.
/// La manera de solucionarlo seria, en lugar de escribir constantemente en el CSV, dumpearlo todo al final, asi nos aseguramos de que todas las filas tienen el mismo numero de variables, aunque
/// esten vacias en las que no se usan.
class CSVSerializer : public ISerializer {
public:
	void openObject(const std::string& name) override;

	void closeObject() override;

private:
	int _currentEvent = -1;

	int _currentHeaderNum = 0;

	std::vector<std::vector<std::pair<std::string, std::any>>> _lines;

	std::unordered_set<std::string> _headers;

	std::unordered_map<std::string, int> _headerOrder;

	const std::string init() override;

	void openEvent() override;

	const std::string dump() override;

	const std::string release() override;

	void serialize_impl(int number, const std::string& name) override;

	void serialize_impl(int64_t number, const std::string& name) override;

	void serialize_impl(float number, const std::string& name) override;

	void serialize_impl(double number, const std::string& name) override;

	void serialize_impl(bool value, const std::string& name) override;

	void serialize_impl(char value, const std::string& name) override;

	void serialize_impl(const std::string& value, const std::string& name) override;

	void checkHeader(const std::string& headerName);

	const std::string anyToString(const std::any& a);
};

#endif