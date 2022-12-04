# Makefile for dayTrip

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: testDayTrip

testDayTrip: testDayTrip.c dayTrip.c Graph.c
	$(CC) $(CFLAGS) -o testDayTrip testDayTrip.c dayTrip.c Graph.c

clean:
	rm -f testDayTrip

