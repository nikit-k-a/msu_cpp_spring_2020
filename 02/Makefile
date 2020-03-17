CC=g++

all: test

test.o: test.cpp Callback.h
	$(CC) -c test.cpp

Callback.o: Callback.cpp Callback.h
	$(CC) -c Callback.cpp

Call: test.o Callback.o
	$(CC) -o Call test.o Callback.o

test: Call
	./Call

clean:
	rm -rf *.o test
	rm -rf *.o Call
