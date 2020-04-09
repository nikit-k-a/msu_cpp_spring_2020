CC=g++

all: test

test.o: test.cpp BigInt.h
	$(CC) -c test.cpp

BigInt.o: BigInt.cpp BigInt.h
	$(CC) -c BigInt.cpp

Big: test.o BigInt.o
	$(CC) -o Big test.o BigInt.o

test: Big
	./Big

clean:
	rm -rf *.o test
	rm -rf *.o Big
