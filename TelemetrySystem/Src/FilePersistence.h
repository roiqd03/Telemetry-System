#pragma once
#include "Persistence.h"
#include <iostream>
class FilePersistence : public Persistence
{
public:
	FilePersistence();
	bool Init(std::string fileDirectory);
	void Release() override;
protected:
	void Flush() override;
	std::string _fileDirectory;
	FILE* _outfile;
};