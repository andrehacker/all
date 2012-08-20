#include <iostream>
#include <string>
#include <memory>
#include <QtGui/QApplication>
#include <QDebug>
#include "textfilelogger.h"
#include "databaseconnection.h"
#include "mainwindow.h"
#include "presenter.h"

/*
* This will only compile using MinGW make (not cygwin): mingw32-make
* Compilation process:
* 1) qmake -project		// creates the project file (.pro)
* 2) qmake				// creates the Makefile
* 3) mingw32-make		// runs the Makefile
*/

int main(int argc, char *argv[])
{
    // Init Logger
    TextFileLogger logger("log.txt");   // RAII - close log at end
    qInstallMsgHandler(TextFileLogger::fileMessageHandler);
    qDebug() << "";
    qDebug() << "Program started";

    // Init Database
    DatabaseConnection db;

    // Init qt-application (required for the view)
    QApplication a(argc, argv);
    MainWindow mainWindow;

    // Init Presenter (MVP). Presenter will init the View (MainWindow)
    Presenter presenter(db, mainWindow);

    return a.exec();
}
