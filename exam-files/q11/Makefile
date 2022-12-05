# findShortestSublist

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined

all: testFindShortestSublist

testFindShortestSublist: testFindShortestSublist.c findShortestSublist.c list.c
	$(CC) $(CFLAGS) -o testFindShortestSublist testFindShortestSublist.c findShortestSublist.c list.c

clean:
	rm -f testFindShortestSublist

