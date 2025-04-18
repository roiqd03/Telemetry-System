#ifndef UAJ2425_G05_JSONSERIALIZER_H
#define UAJ2425_G05_JSONSERIALIZER_H

#include "../ISerializer.h"

/// @brief Serializador a archivos JSON
class JSONSerializer : public ISerializer {
	 const std::string serializeInt8(int8_t number, const std::string& name) override;

	 const std::string serializeUint8(uint8_t number, const std::string& name) override;

	 const std::string serializeInt16(int16_t number, const std::string& name) override;

	 const std::string serializeUint16(uint16_t number, const std::string& name) override;

	 const std::string serializeInt32(int32_t number, const std::string& name) override;

	 const std::string serializeUint32(uint32_t number, const std::string& name) override;

	 const std::string serializeInt64(int64_t number, const std::string& name) override;

	 const std::string serializeUint64(uint64_t number, const std::string& name) override;

	 const std::string serializeFloat(float number, const std::string& name) override;

	 const std::string serializeDouble(double number, const std::string& name) override;

	 const std::string serializeBool(bool value, const std::string& name) override;

	 const std::string serializeString(const std::string& value, const std::string& name) override;
};

#endif