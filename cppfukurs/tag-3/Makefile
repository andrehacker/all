
# Variables
TARGET = tag3
SOURCES = tag3.cpp
HEADERS = tier.hpp tier-template.hpp

# First rule, default target
tag2: $(SOURCES) $(HEADERS)
	g++ -std=c++0x -o $(TARGET) $(SOURCES)


# Clean rule. Best practice to include this
clean: 
	rm -f $(TARGET)
