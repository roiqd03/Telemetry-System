#include "FilePersistence.h"
#include <iostream>
#include <fstream>

void FilePersistence::Flush()
{
	std::ofstream outfile(fileDirectory, std::ios::trunc);
	outfile << SuddenSerialization() << std::endl;
	outfile.close();
}
