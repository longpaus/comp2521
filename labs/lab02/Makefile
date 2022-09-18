# COMP2521 - Lab 02 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: runListQueue runArrayQueue runCircularArrayQueue \
     testListQueue testArrayQueue testCircularArrayQueue

runListQueue: runQueue.o ListQueue.o
	$(CC) $(CFLAGS) -o runListQueue runQueue.o ListQueue.o

runArrayQueue: runQueue.o ArrayQueue.o
	$(CC) $(CFLAGS) -o runArrayQueue runQueue.o ArrayQueue.o

runCircularArrayQueue: runQueue.o CircularArrayQueue.o
	$(CC) $(CFLAGS) -o runCircularArrayQueue runQueue.o CircularArrayQueue.o

testListQueue: testQueue.o ListQueue.o
	$(CC) $(CFLAGS) -o testListQueue testQueue.o ListQueue.o

testArrayQueue: testQueue.o ArrayQueue.o
	$(CC) $(CFLAGS) -o testArrayQueue testQueue.o ArrayQueue.o

testCircularArrayQueue: testQueue.o CircularArrayQueue.o
	$(CC) $(CFLAGS) -o testCircularArrayQueue testQueue.o CircularArrayQueue.o

runQueue.o: runQueue.c Queue.h
testQueue.o: testQueue.c Queue.h

ListQueue.o: ListQueue.c Queue.h
ArrayQueue.o: ArrayQueue.c Queue.h
CircularArrayQueue.o: CircularArrayQueue.c Queue.h

.PHONY: clean
clean:
	rm -f runListQueue runArrayQueue runCircularArrayQueue \
	      testListQueue testArrayQueue testCircularArrayQueue \
	      *.o

