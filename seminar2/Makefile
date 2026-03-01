CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

all: task1 task2 task3

task1: task1.cpp
	$(CXX) $(CXXFLAGS) -o task1 task1.cpp

task2: task2.cpp
	$(CXX) $(CXXFLAGS) -o task2 task2.cpp

task3: task3.cpp
	$(CXX) $(CXXFLAGS) -o task3 task3.cpp

run1: task1
	./task1

run2: task2
	./task2

run3: task3
	./task3

clean:
	rm -f task1 task2 task3

.PHONY: all run1 run2 run3 clean
