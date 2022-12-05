// Main program for testing closeFollowers

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void closeFollowers(Graph g, int src, int distance, int followers[]);

int main(void) {
    int nV;
    if (scanf("nV: %d ", &nV) != 1) {
        printf("error: failed to read nV\n");
        return 1;
    }

    int src;
    if (scanf("src: %d ", &src) != 1) {
        printf("error: failed to read src\n");
        return 1;
    }

    int distance;
    if (scanf("distance: %d ", &distance) != 1) {
        printf("error: failed to read distance\n");
        return 1;
    }

    printf("nV: %d\nsrc: %d\n\n", nV, src);

    Graph g = GraphNew(nV);
    int s, d;
    while (scanf("%d %d", &s, &d) == 2) {
        GraphInsertEdge(g, s, d);
        printf("Edge inserted: %d -> %d\n", s, d);
    }
    printf("\n");

    int *followers = malloc(nV * sizeof(int));
    assert(followers != NULL);
    for (int i = 0; i < nV; i++) {
        followers[i] = -1.0;
    }

    closeFollowers(g, src, distance, followers); 

    printf("Close followers of node %d, distance %d:\n", src, distance);
    for (int i = 0; i < nV; i++) {
        if (followers[i] == 1) {
            printf(" node %d\n", i);
        }
    }
    printf("\n");

    free(followers);
    GraphFree(g);
}

