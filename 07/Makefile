CC=g++

all: test

test.o: test.cpp My_vector.h
	$(CC) -c test.cpp

Vect: test.o
	$(CC) -o Vect test.o 

test: Vect
	./Vect

clean:
	rm -rf *.o test
	rm -rf *.o Vect
