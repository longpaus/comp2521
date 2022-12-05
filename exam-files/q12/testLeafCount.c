// Main program for testing leafCount

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int leafCount(BSTree t, int pathLength);

int main(int argc, char *argv[]) {
    char buffer[1024];

    char *line = fgets(buffer, sizeof(buffer), stdin);
    BSTree t = BSTreeRead(line);
    printf("\nTree:\n\n");
    BSTreeShow(t);

    int pathLength = 0;
    if (scanf("%d", &pathLength) != 1) {
        printf("error: failed to read pathLength\n");
        return 1;
    }
    printf("\npathLength: %d\n", pathLength);

    int ans = leafCount(t, pathLength);
    printf("leafCount returned: %d\n", ans);

    BSTreeFree(t);
}

