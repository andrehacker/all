#include <QtGui/QApplication>
#include "mainwindow.h"
#include "textfilelogger.h"
#include <iostream>
#include <string>
#include <QtDebug>

/*
* This will only compile using MinGW make (not cygwin): mingw32-make
* Compilation process:
* 1) qmake -project		// creates the project file (.pro)
* 2) qmake				// creates the Makefile
* 3) mingw32-make		// runs the Makefile
*/

int main(int argc, char *argv[])
{
    TextFileLogger logger("log.txt");   // RAII - close log at end
    qInstallMsgHandler(TextFileLogger::fileMessageHandler);

    qDebug() << "Program started";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
