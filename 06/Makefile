CC=g++

all: test

test.o: test.cpp Printer.h
	$(CC) -c test.cpp

Prt: test.o
	$(CC) -o Prt test.o 

test: Prt
	./Prt

clean:
	rm -rf *.o test
	rm -rf *.o Prt
