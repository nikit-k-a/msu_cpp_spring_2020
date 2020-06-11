CC=g++

test: Summator
	./Summator

Summator: main.o Summator.o
	$(CC) -o Summator main.o Summator.o -lpthread

main.o: main.cpp Summator.h
	$(CC) -c main.cpp

Summator.o: Summator.cpp Summator.h
	$(CC) -c Summator.cpp

clean:
	rm -rf *.o Summator
