CXX = g++
CXXFLAGS = -std=c++17 -I.
SOURCES = main.cpp src/lexer/lexer.cpp src/parser/parser.cpp src/interpreter/interpreter.cpp
TARGET = cerberus

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
