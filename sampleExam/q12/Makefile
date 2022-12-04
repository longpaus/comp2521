# Makefile for minDiff

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: testMinDiff

testMinDiff: testMinDiff.c minDiff.c BSTree.c
	$(CC) $(CFLAGS) -o testMinDiff testMinDiff.c minDiff.c BSTree.c

clean:
	rm -f testMinDiff

