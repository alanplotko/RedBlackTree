CC=g++
CPPFLAGS=-g -Wall

all: main

main: main.o
	$(CC) -std=c++11 main.o -o main

main.o: main.cpp rbt.h rbt.cpp
	$(CC) -std=c++11 -c main.cpp

clean:
	rm *.o *~ -f main
