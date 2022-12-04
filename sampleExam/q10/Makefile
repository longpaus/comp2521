# Makefile for maxDegreeDiff

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: testMaxDegreeDiff

testMaxDegreeDiff: testMaxDegreeDiff.c maxDegreeDiff.c Graph.c
	$(CC) $(CFLAGS) -o testMaxDegreeDiff testMaxDegreeDiff.c maxDegreeDiff.c Graph.c

clean:
	rm -f testMaxDegreeDiff

