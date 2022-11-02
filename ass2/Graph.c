#include <stdio.h>

typedef struct adjNode *AdjList;
struct adjNode {
    int v;
    AdjList next;
};

struct Graph {
    int numVertices;
};
