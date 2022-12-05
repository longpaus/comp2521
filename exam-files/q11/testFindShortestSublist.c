// Main program for testing findShortestSublist

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List findShortestSublist(List l, int start, int end);

int main(int argc, char *argv[]) {
    char buffer[1024];

    char *line = fgets(buffer, sizeof(buffer), stdin);
    List l = ListRead(line);
    printf("list: ");
    ListShow(l);

    int start = 0;
    scanf("%d", &start);
    printf("start: %d\n", start);

    int end = 0;
    scanf("%d", &end);
    printf("end: %d\n", end);

    List ans = findShortestSublist(l, start, end);
    printf("shortest sublist: ");
    ListShow(ans);

    ListFree(ans);
    ListFree(l);
}

