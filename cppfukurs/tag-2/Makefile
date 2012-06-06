
# Variables
TARGET = tag2
SOURCES = tag2.cpp
HEADERS =  Complex.hpp

# First rule, default target
tag2: $(SOURCES) $(HEADERS)
	g++ -std=c++0x -o $(TARGET) $(SOURCES)


# Clean rule. Best practice to include this
clean: 
	rm -f $(TARGET)
