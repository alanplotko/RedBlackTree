CC=g++
CPPFLAGS=-g -Wall

all: main

main: avl.o main.o
    $(CC) -std=c++11 avl.o main.o -o main

main.o: main.cpp
    $(CC) -std=c++11 -c main.cpp

avl.o: avl.h avl.cpp
    $(CC) -std=c++11 -c avl.cpp

clean:
    rm *.o *~ -f main
