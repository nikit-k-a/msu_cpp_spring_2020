CC=g++

all: test

test.o: test.cpp sorter.h
	$(CC) -c test.cpp

sorter.o: sorter.cpp sorter.h
	$(CC) -c sorter.cpp

Srt: test.o sorter.o
	$(CC) -o Srt test.o sorter.o -lpthread 

test: Srt
	./Srt

clean:
	rm -rf *.o test
	rm -rf *.o Srt


