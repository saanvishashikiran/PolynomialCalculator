# Makefile for Data Structures Assignment #1

# variables
CXX = g++                  # C++ compiler
CXXFLAGS = -Wall -std=c++11 # compiler flags: enable all warnings, use C++11 standard
OBJ = Polynomial.o main.o  # object files
TARGET = a.out             # name of the final executable

# default target
all: $(TARGET)

# linking object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# compile Polynomial.cpp into Polynomial.o
Polynomial.o: Polynomial.cpp Polynomial.h
	$(CXX) $(CXXFLAGS) -c Polynomial.cpp

# compile main.cpp into main.o
main.o: main.cpp Polynomial.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# clean up build files
clean:
	rm -f $(OBJ) $(TARGET)
