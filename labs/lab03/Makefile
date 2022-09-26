# COMP2521 - Lab 03 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: sortIntList benchmarkArrayQueue benchmarkCircularArrayQueue

sortIntList: sortIntList.o IntList.o
	$(CC) $(CFLAGS) -o sortIntList sortIntList.o IntList.o

benchmarkArrayQueue: benchmarkQueue.o ArrayQueue.o
	$(CC) $(CFLAGS) -o benchmarkArrayQueue benchmarkQueue.o ArrayQueue.o

benchmarkCircularArrayQueue: benchmarkQueue.o CircularArrayQueue.o
	$(CC) $(CFLAGS) -o benchmarkCircularArrayQueue benchmarkQueue.o CircularArrayQueue.o

sortIntList.o: sortIntList.c IntList.h
benchmarkQueue.o: benchmarkQueue.c Queue.h

IntList.o: IntList.c IntList.h
ArrayQueue.o: ArrayQueue.c Queue.h
CircularArrayQueue.o: CircularArrayQueue.c Queue.h

.PHONY: clean
clean:
	rm -rf sortIntList benchmarkArrayQueue benchmarkCircularArrayQueue *.o

