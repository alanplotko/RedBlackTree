CC=g++
CPPFLAGS=-g -Wall

all: main

main: rbt.o main.o
	$(CC) -std=c++11 rbt.o main.o -o main

main.o: main.cpp
	$(CC) -std=c++11 -c main.cpp

rbt.o: rbt.h rbt.cpp
	$(CC) -std=c++11 -c rbt.cpp

clean:
	rm *.o *~ -f main
