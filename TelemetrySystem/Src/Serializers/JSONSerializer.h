#ifndef UAJ2425_G05_JSONSERIALIZER_H
#define UAJ2425_G05_JSONSERIALIZER_H

#include "../ISerializer.h"
#include <nlohmann/json.hpp>
#include <deque>

/// @brief Serializador a archivos JSON
class JSONSerializer : public ISerializer {
public:
	void openObject(const std::string& name) override;

	void closeObject() override;

private:
	int _createdObjects = 0;

	std::deque<nlohmann::json> _objectStack;

	void init(std::nullptr_t dummy, ...) override;

	void openEvent() override;

	const std::string dump() override;

	void release() override;

	void serialize_impl(int number, const std::string& name) override;

	void serialize_impl(int64_t number, const std::string& name) override;

	void serialize_impl(float number, const std::string& name) override;

	void serialize_impl(double number, const std::string& name) override;

	void serialize_impl(bool value, const std::string& name) override;

	void serialize_impl(char value, const std::string& name) override;

	void serialize_impl(const std::string& value, const std::string& name) override;
};

#endif