.PHONY: all compile run doc clean
.DEFAULT_GOAL = compile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
LDFLAGS = -lncurses
EXECUTABLE = tarotoma
SOURCES := $(wildcard src/*.cpp)
-include $(SOURCES:.cpp=.d)

%.o: %.cpp
	@echo "$^ -> $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ -c $< $(LDFLAGS)
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp $(LDFLAGS) > $*.d

all: compile

compile: $(SOURCES:.cpp=.o)
	@echo "Compiling..."
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LDFLAGS)
	@echo "Done!"

run: compile
	@echo "Starting executable..."
	@./$(EXECUTABLE)
	@echo "Done!"

doc:
	@echo "Generating docs..."
	doxygen Doxyfile
	@echo "Done!"

clean:
	@echo "Removing object files..."
	@rm -f -- src/*.o
	@echo "Removing executable file..."
	@rm -f $(EXECUTABLE)
	@echo "Removing link files..."
	@rm -f -- src/*.d
	@echo "Removing docs..."
	@rm -rf -- doc/
	@echo "Done!"