# Andre Hacker 2012-07-26
# compiled with cygwin!
# Variables
TARGET = main
SOURCES = main.cpp hotkey.cpp
HEADERS =  hotkey.h

# First rule, default target
# quicknote: $(SOURCES) $(HEADERS)
quicknote: $(SOURCES) $(HEADERS)
	g++ -std=c++0x -o $(TARGET) $(SOURCES)


# Clean rule. Best practice to include this
clean: 
	rm -f $(TARGET)
