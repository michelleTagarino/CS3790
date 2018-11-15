# Michelle Tagarino
# makefile for Lab Assignment #2: Threads in Java

JCC = javac
JFLAGS = -g

default : PrimeThreads.class Threads.class

PrimeThreads.class : Threads.java
	$(JCC) $(JFLAGS) Threads.java

Threads.class : Threads.java
	$(JCC) $(JFLAGS) Threads.java

clean:
	$(RM) *.class
