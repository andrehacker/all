# 
# This is a GNU make input file for HttpServer
# 
# Rules are essential part of the make file. Rule looks like:
# Target: Dependencies
# 	Command 1
# 	Command 2...
# 
# Commands are executed in a separate shell. Dependencies are space separated
# Command could be @echo "Deleting files..."
# @ means supress command echo
# 

# Variables
TARGET = webserver
OBJECTFILES = main.o HttpServer.o
HEADERS = HttpServer.h
BOOSTDIR = /home/andre/DEV/boost_1_48_0/include/
BOOSTDIRLIBS = /home/andre/DEV/boost_1_48_0/lib/

# First rule is the default target, usually the final executable(s)
webserver: $(OBJECTFILES) $(HEADERS)
	g++ -std=c++0x -I$(BOOSTDIR) -L$(BOOSTDIRLIBS) $(OBJECTFILES) -o $(TARGET) -lboost_system -lboost_thread -lpthread
#	g++ -std=c++0x -I$(BOOSTDIR) -L$(BOOSTDIRLIBS) -o $(TARGET) main.cpp  HttpServer.cpp -lboost_system -lboost_thread -lpthread
# Old comment: Two working ways:
# g++ -std=c++0x -I/home/andre/DEV/boost_1_48_0/include/ -L/home/andre/DEV/boost_1_48_0/lib/ -o webserver main.cpp  HttpServer.cpp -lboost_system -lboost_thread -lpthread
# g++ -std=c++0x -I/home/andre/DEV/boost_1_48_0/include/ main.cpp HttpServer.cpp -o webserver -L/home/andre/DEV/boost_1_48_0/lib/ -lpthread -lboost_thread -lboost_system
# c++ -I path/to/boost_1_48_0 example.cpp -o example -L~/boost/stage/lib/ -lboost_regex-gcc34-mt-d-1_36 (proposed by boost tutorial)


# Rule to compile main.cpp
main.o: main.cpp HttpServer.cpp HttpServer.o
	g++ -std=c++0x -c main.cpp

# Rule to compiling HttpServer
HttpServer.o: HttpServer.cpp HttpServer.h
	g++ -std=c++0x -I$(BOOSTDIR) -L$(BOOSTDIRLIBS) -c HttpServer.cpp -lboost_system -lboost_thread -lpthread

# Clean rule. Best practice to include this
clean: 
	rm -f $(TARGET) $(OBJECTFILES)
