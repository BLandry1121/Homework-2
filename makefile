CC=g++

all: main.o
	$(CC) -std=c++11 main.o

main: main.o
	$(CC) -c -std=c++11 main.cpp

clean:
	rm -f *.o *.out
