#include "textfilelogger.h"
#include <fstream>
#include <QtGlobal>

std::ofstream TextFileLogger::logfile;

TextFileLogger::TextFileLogger(const char *filename) {
	logfile.open(filename, std::ios::out | std::ios::app);
}

TextFileLogger::~TextFileLogger() {
	logfile << "Closing file" << std::endl;
	logfile.close();
}

void TextFileLogger::fileMessageHandler(QtMsgType type, const char *msg) {
	logfile << msg << std::endl;
}