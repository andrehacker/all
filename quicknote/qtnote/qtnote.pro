######################################################################
# Automatically generated by qmake (2.01a) Mo 30. Jul 19:43:27 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += abstractview.h mainwindow.h textfilelogger.h stringlistmodel.h sqlite3.h \
    sqlite.h \
    sqlitetable.h \
    notemodel.h \
    tagmodel.h \
    notetable.h \
    databaseconnection.h \
    sqlitequery.h \
    presenter.h \
    globalhotkey.h \
    notesuimodel.h
FORMS += mainwindow.ui
SOURCES += globalhotkey.cpp main.cpp mainwindow.cpp textfilelogger.cpp stringlistmodel.cpp sqlite3.c \
    sqlite.cpp \
    sqlitetable.cpp \
    notemodel.cpp \
    tagmodel.cpp \
    notetable.cpp \
    databaseconnection.cpp \
    sqlitequery.cpp \
    presenter.cpp \
    notesuimodel.cpp
# QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x

RESOURCES += \
    res.qrc