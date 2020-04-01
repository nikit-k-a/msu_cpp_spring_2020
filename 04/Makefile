CC=g++

all: test

test.o: test.cpp Serializer.h
	$(CC) -c test.cpp

Ser: test.o
	$(CC) -o Ser test.o 

test: Ser
	./Ser

clean:
	rm -rf *.o test
	rm -rf *.o Ser
