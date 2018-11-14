# Michelle Tagarino
# makefile for the Memory Simulation program using linked lists (Final Assignment)

main : memory.o main.o
	g++ memory.o main.o -o main

memory.o : memory.cpp
	g++ -std=c++11 -c memory.cpp

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o main
