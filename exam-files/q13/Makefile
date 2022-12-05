# closeFollowers

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined

all: testCloseFollowers

testCloseFollowers: testCloseFollowers.c closeFollowers.c Graph.c
	$(CC) $(CFLAGS) -o testCloseFollowers testCloseFollowers.c closeFollowers.c Graph.c

clean:
	rm -f testCloseFollowers

