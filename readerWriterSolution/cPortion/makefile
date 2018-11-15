# makefile for the dictionary program using linked linked (Take Home Assignment #3)

main : readerwriter.o main.o
	gcc readerwriter.o main.o -lpthread -o main

readerwriter.o : readerwriter.c
	gcc -c readerwriter.c

main.o : main.c
	gcc -c main.c

clean:
	rm *.o main
