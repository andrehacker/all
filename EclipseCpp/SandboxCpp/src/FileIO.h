#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <string>
using namespace std;

class FileIO {

public:

	FileIO() {};
	~FileIO() {};

	string readAsChar(string filename);

};

#endif
