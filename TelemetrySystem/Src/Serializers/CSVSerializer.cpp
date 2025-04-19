#include "CSVSerializer.h"

const std::string CSVSerializer::init() {
	// Init no tiene que hacer nada, puesto que para ahorrarnos problemas, el CSV no va a tener cabecera, no tiene que escribir nada.
	return "";
}

void CSVSerializer::openEvent() {
	_lines.push_back(std::vector<std::pair<std::string, std::any>>());
	++_currentEvent;
}

const std::string CSVSerializer::release() {
	// Release no hace nada, porque los archivos CSV no tienen caracter de terminacion como otros formatos.
	return "";
}

void CSVSerializer::openObject(const std::string& name) {
	// CSV no tiene objetos complejos, por lo que estas instrucciones simplemente no haran nada. En otros lenguajes, como JSON o YAML, crearan un objeto.
}

void CSVSerializer::closeObject() {
	// Lo mismo que openObject.
}

const std::string CSVSerializer::dump() {
	std::string s = "";
	for (int i = 0; i < _lines.size(); ++i) {
		std::vector<std::pair<bool, int>> tmp(_headers.size(), {false, -1});
		for (int j = 0; j < _lines[i].size(); ++j) {
			tmp[_headerOrder[_lines[i][j].first]] = { true, j };
		}

		for (int k = 0; k < tmp.size(); ++k) {
			s += tmp[k].first ? anyToString(_lines[i][tmp[k].second].second) : "";
			if (k != tmp.size() - 1) s += ",";
		}
		s += "\n";
	}
	_lines.clear();
	_currentEvent = -1;
	return s;
}

void CSVSerializer::serialize_impl(int number, const std::string& name) {
	_lines[_currentEvent].push_back({ name, number });
	checkHeader(name);
}

void CSVSerializer::serialize_impl(int64_t number, const std::string& name) {
	_lines[_currentEvent].push_back({ name, number });
	checkHeader(name);
}

void CSVSerializer::serialize_impl(float number, const std::string& name) {
	_lines[_currentEvent].push_back({ name, number });
	checkHeader(name);
}

void CSVSerializer::serialize_impl(double number, const std::string& name) {
	_lines[_currentEvent].push_back({ name, number });
	checkHeader(name);
}

void CSVSerializer::serialize_impl(bool value, const std::string& name) {
	_lines[_currentEvent].push_back({ name, value });
	checkHeader(name);
}

void CSVSerializer::serialize_impl(char value, const std::string& name) {
	_lines[_currentEvent].push_back({ name, value });
	checkHeader(name);
}

void CSVSerializer::serialize_impl(const std::string& value, const std::string& name) {
	_lines[_currentEvent].push_back({ name, value });
	checkHeader(name);
}

void CSVSerializer::checkHeader(const std::string& headerName) {
	if (_headers.count(headerName) == 0) {
		_headers.insert(headerName);
		_headerOrder[headerName] = _currentHeaderNum;
		++_currentHeaderNum;
	}
}

const std::string CSVSerializer::anyToString(const std::any& a) {
	if (a.type() == typeid(int)) return std::to_string(std::any_cast<int>(a));
	else if (a.type() == typeid(int64_t)) return std::to_string(std::any_cast<int64_t>(a));
	else if (a.type() == typeid(float)) return std::to_string(std::any_cast<float>(a));
	else if (a.type() == typeid(double)) return std::to_string(std::any_cast<double>(a));
	else if (a.type() == typeid(bool)) return std::any_cast<bool>(a) ? "true" : "false";
	else if (a.type() == typeid(char)) return std::to_string(std::any_cast<char>(a));
	else if (a.type() == typeid(std::string)) return std::any_cast<std::string>(a);
	else return "";
}