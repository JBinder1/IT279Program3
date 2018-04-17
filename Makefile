CC=g+
CFLAGS=-std=c++11 -Wall
OUTPUTNAME=Spellcheck

all: Dictionary main
	$(CC) $(CFLAGS) *.o -o $(OUTPUTNAME)

Dictionary: Dictionary.cpp
	$(CC) $(CFLAGS) -c Dictionary.cpp

main: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o
	rm $(OUTPUTNAME)