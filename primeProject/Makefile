#James Nolan C00226267
#Makefile for Primes Project
#Used to contain commands to compile projects

CC=g++
CFLAGS= -std=c++11 -pthread

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS) -fopenmp

TWINCON: twinPrimes.o
	$(CC) -o twinPrimes twinPrimes.o -fopenmp $(CFLAGS) $(DEBUGFLAGS)

TWINSEQ: twinPrimesSeq.o
	$(CC) -o twinPrimesSeq twinPrimesSeq.o $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
