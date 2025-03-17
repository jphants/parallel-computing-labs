CXX = g++
CXXFLAGS = -g -Wall -std=c++17  # Habilita depuración (-g) y elimina optimización (-O2)

TARGETS = nested_loops matrix_classic matrix_block

all: clean $(TARGETS)  # Primero limpia, luego compila

nested_loops: nested_loops.cpp
	$(CXX) $(CXXFLAGS) -o nested_loops nested_loops.cpp

matrix_classic: matrix_classic.cpp
	$(CXX) $(CXXFLAGS) -o matrix_classic matrix_classic.cpp

matrix_block: matrix_block.cpp
	$(CXX) $(CXXFLAGS) -o matrix_block matrix_block.cpp

clean:
	rm -f $(TARGETS)
