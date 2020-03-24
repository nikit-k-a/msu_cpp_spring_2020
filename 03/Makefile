CC=g++

all: test

test.o: test.cpp Matrix.h
	$(CC) -c test.cpp

Callback.o: Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp

Mx: test.o Matrix.o
	$(CC) -o Mx test.o Matrix.o

test: Mx
	./Mx

clean:
	rm -rf *.o test
	rm -rf *.o Mx
