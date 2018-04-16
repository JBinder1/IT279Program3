CC=g++
CFLAGS=-std=c++11 -Wall
OUTPUTNAME=Spellcheck

all: Dictionary main
	$(CC) $(CFLAGS) *.o -o $(OUTPUTNAME)

InsertionSort: InsertionSort.cpp
	$(CC) $(CFLAGS) -c main.cpp

main: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o
rm $(OUTPUTNAME)
