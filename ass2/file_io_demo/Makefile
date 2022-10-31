
CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: linenos catalogue

linenos: linenos.c
catalogue: catalogue.c

.PHONY: clean
clean:
	rm -f linenos catalogue

