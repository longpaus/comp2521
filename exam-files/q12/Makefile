# leafCount

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined

all: testLeafCount

testLeafCount: testLeafCount.c leafCount.c BSTree.c
	$(CC) $(CFLAGS) -o testLeafCount testLeafCount.c leafCount.c BSTree.c

clean:
	rm -f testLeafCount

