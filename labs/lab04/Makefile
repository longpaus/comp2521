# COMP2521 - Lab 04 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

COMMON_OBJS = StudentDb.o Tree.o List.o Record.o

.PHONY: all
all: runTest runDb

runTest: runTest.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o runTest runTest.o $(COMMON_OBJS)

runDb: runDb.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o runDb runDb.o $(COMMON_OBJS)

runTest.o: runTest.c Tree.h List.h Record.h
runDb.o: runDb.c StudentDb.h List.h Record.h

StudentDb.o: StudentDb.c List.h Record.h Tree.h
Tree.o: Tree.c Tree.h List.h
List.o: List.c List.h
Record.o: Record.c Record.h

.PHONY: clean
clean:
	rm -f *.o runTest runDb

