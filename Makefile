CXX = g++
CXXFLAGS = -std=c++17 -I.
LIB_SOURCES = src/lexer/lexer.cpp src/parser/parser.cpp src/interpreter/interpreter.cpp
SOURCES = main.cpp $(LIB_SOURCES)
TARGET = cerberus

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) tests/test_features.cpp $(LIB_SOURCES) -o test_features
	./test_features

clean:
	rm -f $(TARGET) test_features

.PHONY: test clean
