//============================================================================
// Name        : SandboxCpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "FileIO.h"
using namespace std;

int main() {
	FileIO* io = new FileIO();
	cout << "Sandbox" << endl; // prints Sandbox
	cout << "Open file: " << io->readAsChar("test.dat");
	return 0;
}
