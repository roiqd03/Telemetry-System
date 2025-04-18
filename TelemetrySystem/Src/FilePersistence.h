#pragma once
#include "Persistence.h"
#include <iostream>
class FilePersistence : public Persistence
{
public:
	FilePersistence(std::string fileDirectory);
	bool Init() override;
	void Release() override;
protected:
	void Flush() override;
	std::string _fileDirectory;
	FILE* _outfile;
};