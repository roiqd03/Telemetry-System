#include "FilePersistence.h"
#include <fstream>
#include "ISerializer.h"

FilePersistence::FilePersistence(std::string fileDirectory) : Persistence()
{
	_outfile = nullptr;
	_fileDirectory = fileDirectory;
}

bool FilePersistence::Init()
{
	fopen_s(&_outfile, _fileDirectory.c_str(), "a");
	if (_outfile == nullptr) return false;
	std::string s = _serializer->init();
	fwrite(s.c_str(), s.length(), 1, _outfile);
	return true;
}

void FilePersistence::Release()
{
	std::string s = _serializer->release();
	fwrite(s.c_str(), s.length(), 1, _outfile);
	fclose(_outfile);
}

void FilePersistence::Flush()
{
	std::string s = SuddenSerialization();
	fwrite(s.c_str(), s.length(), 1, _outfile);
}
