#include "FilePersistence.h"
#include <fstream>

FilePersistence::FilePersistence(std::string fileDirectory) : Persistence()
{
	_fileDirectory = fileDirectory;
}

bool FilePersistence::Init()
{
	_outfile = std::ofstream(_fileDirectory, std::ios::app);
	return true;
}

void FilePersistence::Release()
{
	_outfile.close();
}

void FilePersistence::Flush()
{
	_outfile << SuddenSerialization() << std::endl;
}
