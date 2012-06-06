
# Variables
TARGET = tag1
SOURCES = tag1.cpp tag1-aufgabe3.cpp fibo.cpp
HEADERS =  tag1-aufgabe3.hpp Tuple.hpp

# First rule, default target
webserver: $(SOURCES) $(HEADERS)
	g++ -std=c++0x -o $(TARGET) $(SOURCES)


# Clean rule. Best practice to include this
clean: 
	rm -f $(TARGET)
