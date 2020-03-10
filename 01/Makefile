CC=g++

# all: my_pr1

all: Allocator.o
	# $(CC) -o my_pr1 Allocator.o

Allocator.o: Allocator.cpp Allocator.h
	$(CC) -c Allocator.cpp

test: test.o
	$(CC) -o test test.o
	./test

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o my_pr1
	rm -rf *.o test
