#pragma once
#include "Persistence.h"
class FilePersistence : public Persistence
{
protected:
	void Flush() override;
	std::string fileDirectory;
};

