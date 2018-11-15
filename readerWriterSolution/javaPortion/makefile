# Michelle Tagarino
# makefile for Lab Assignment #3: Reader/Writer Solution in Java

JCC = javac
JFLAGS = -g

default : Reader.class Writer.class ReadWrite.class

Reader.class : ReadWrite.java
	$(JCC) $(JFLAGS) ReadWrite.java

Writer.class : ReadWrite.java
	$(JCC) $(JFLAGS) ReadWrite.java

ReadWrite.class : ReadWrite.java
	$(JCC) $(JFLAGS) ReadWrite.java

clean:
	$(RM) *.class
