#include "JSONSerializer.h"

void JSONSerializer::init(std::nullptr_t dummy, ...) {
	/// El serializador de JSON no necesita que le pasemos ningun argumento.
    _initialWrite = "[";
}

void JSONSerializer::openEvent() {
	_objectStack.push_back(nlohmann::json::object());
}

const std::string JSONSerializer::release() {
	return "]";
}

void JSONSerializer::openObject(const std::string& name) {
	nlohmann::json::object_t obj = nlohmann::json::object();
	_objectStack.back()[name] = obj;
	_objectStack.push_back(obj);
	++_createdObjects;
}

void JSONSerializer::closeObject() {
	if (_createdObjects > 0) {
		_objectStack.pop_back();
		--_createdObjects;
	}
}

const std::string JSONSerializer::dump() {
	std::string s = "";
	for (int i = 0; i < _objectStack.size(); ++i) {
		s += _objectStack[i].dump();
		if (i != _objectStack.size() - 1) s += ",";
	}
	_objectStack.clear();
	_createdObjects = 0;
	return s;
}

void JSONSerializer::serialize_impl(int number, const std::string& name) {
	_objectStack.back()[name] = number;
}

void JSONSerializer::serialize_impl(int64_t number, const std::string& name) {
	_objectStack.back()[name] = number;
}

void JSONSerializer::serialize_impl(float number, const std::string& name) {
	_objectStack.back()[name] = number;
}

void JSONSerializer::serialize_impl(double number, const std::string& name) {
	_objectStack.back()[name] = number;
}

void JSONSerializer::serialize_impl(bool value, const std::string& name) {
	_objectStack.back()[name] = value;
}

void JSONSerializer::serialize_impl(char value, const std::string& name) {
	_objectStack.back()[name] = value;
}

void JSONSerializer::serialize_impl(const std::string& value, const std::string& name) {
	_objectStack.back()[name] = value;
}
