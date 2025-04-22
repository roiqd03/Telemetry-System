#include "FilePersistence.h"
#include <fstream>
#include "ISerializer.h"

FilePersistence::FilePersistence() : Persistence()
{
	_outfile = nullptr;
}

bool FilePersistence::Init(std::string fileDirectory)
{
	_fileDirectory = fileDirectory;
	fopen_s(&_outfile, _fileDirectory.c_str(), "a");
	if (_outfile == nullptr) return false;
	std::string s = _serializer->_initialWrite;
	fwrite(s.c_str(), s.length(), 1, _outfile);
	return true;
}

void FilePersistence::Release()
{
	std::string s = _serializer->release();
	if (errno == ENOMEM || errno == ENOSPC) {
		fclose(_outfile);
		remove(_fileDirectory.c_str());
	}
	else {
		size_t length = s.length();
		size_t written = fwrite(s.c_str(), length, 1, _outfile);
		fclose(_outfile);
		if (written != length) {
			if (errno == ENOMEM || errno == ENOSPC) {
				remove(_fileDirectory.c_str());
			}
		}
	}

}

bool FilePersistence::Flush()
{
	std::string s = SuddenSerialization();
	size_t length = s.length();
	size_t written = fwrite(s.c_str(), length, 1, _outfile);
	if (written != length) {
		if (errno == ENOMEM || errno == ENOSPC) {
			return false;
		}
	}
	return true;
}
