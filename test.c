#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   Vertex v;
   struct Node *next;
} Node;

typedef struct GraphRep {
   Node **edges;  // array of lists
   int    nV;     // #vertices
   int    nE;     // #edges
} GraphRep;