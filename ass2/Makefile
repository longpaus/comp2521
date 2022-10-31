# COMP2521 Assignment 2 Makefile
#
# HOW TO USE
# 1. Ensure that your directory structure looks like:
#    ass2/
#        part1/
#            ...
#        part2/
#            ...
#        part3/
#            ...
#        Makefile (this Makefile)
#        pageRank.c
#        searchPageRank.c
#        scaledFootrule.c
#        Your supporting files...
#
# 2. Read all the comments below and edit the Makefile accordingly
#
# 3. After you use the make command, this will create executables in
#    the part1/*, part2/* and part3/* directories. Change into these
#    directories and run your programs.

CC = clang
CFLAGS0 = -Wall -Werror -g
CFLAGS1 = -Wall -Werror -g -fsanitize=address,leak,undefined
CFLAGS2 = -Wall -Werror -g -fsanitize=memory,undefined

# Notes:
# Your pageRank.c should have the main() function for Part 1
# Your searchPageRank.c should have the main() function for Part 2
# Your scaledFootrule.c should have the main() function for Part 3
# List all your C files that DON'T contain a main() function here
# For example: SUPPORTING_FILES = hello.c world.c
SUPPORTING_FILES = 

.PHONY: all
all: pageRank searchPageRank scaledFootrule

pageRank: pageRank.c $(SUPPORTING_FILES)
	$(CC) $(CFLAGS1) -o pageRank pageRank.c $(SUPPORTING_FILES) -lm
	find . -maxdepth 2 -path './part1/*' -exec cp pageRank {} \;
	rm pageRank

searchPageRank: searchPageRank.c $(SUPPORTING_FILES)
	$(CC) $(CFLAGS1) -o searchPageRank searchPageRank.c $(SUPPORTING_FILES) -lm
	find . -maxdepth 2 -path './part2/*' -exec cp searchPageRank {} \;
	rm searchPageRank

scaledFootrule: scaledFootrule.c $(SUPPORTING_FILES)
	$(CC) $(CFLAGS1) -o scaledFootrule scaledFootrule.c $(SUPPORTING_FILES) -lm
	find . -maxdepth 2 -path './part3/*' -exec cp scaledFootrule {} \;
	rm scaledFootrule

.PHONY: clean
clean:
	rm -f pageRank searchPageRank scaledFootrule
	rm -f part1/*/pageRank part2/*/searchPageRank part3/*/scaledFootrule

