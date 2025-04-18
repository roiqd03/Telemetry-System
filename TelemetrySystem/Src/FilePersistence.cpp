#include "FilePersistence.h"
#include <fstream>

FilePersistence::FilePersistence(std::string fileDirectory) : Persistence()
{
	_outfile = nullptr;
	_fileDirectory = fileDirectory;
}

bool FilePersistence::Init()
{
	fopen_s(&_outfile, _fileDirectory.c_str(), "a");
	return _outfile != nullptr;
}

void FilePersistence::Release()
{
	fclose(_outfile);
}

void FilePersistence::Flush()
{
	std::string s = SuddenSerialization();
	fwrite(s.c_str(), s.length(), 1, _outfile);
}
