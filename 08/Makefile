CC=g++

all: test

test.o: test.cpp My_thread_pool.h
	$(CC) -c test.cpp

My_thread_pool.o: My_thread_pool.cpp My_thread_pool.h
	$(CC) -c My_thread_pool.cpp

Pool: test.o My_thread_pool.o
	$(CC) -o Pool test.o My_thread_pool.o -lpthread 

test: Pool
	./Pool

clean:
	rm -rf *.o test
	rm -rf *.o Pool


