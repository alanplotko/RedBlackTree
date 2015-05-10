CC=g++
CPPFLAGS=-g -Wall

all: test-rbt

test-rbt: test-rbt.o
	$(CC) -std=c++11 test-rbt.o -o test-rbt

test-rbt.o: test-rbt.cpp rbt.h rbt.cpp
	$(CC) -std=c++11 -c test-rbt.cpp

clean:
	rm *.o *~ -f test-rbt
