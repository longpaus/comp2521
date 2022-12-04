# Makefile for flas

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: testFlas

testFlas: testFlas.c flas.c list.c
	$(CC) $(CFLAGS) -o testFlas testFlas.c flas.c list.c

clean:
	rm -f testFlas

