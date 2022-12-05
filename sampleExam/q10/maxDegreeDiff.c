
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
static int outDegree(Graph g,Vertex v);
static int inDegree(Graph g,Vertex v);
int maxDegreeDiff(Graph g) {
    int max = -1;
    for(Vertex v = 0; v < g->nV; v++){
        int absDegDiff = abs(inDegree(g,v) - outDegree(g,v));
        if(absDegDiff > max){
            max = absDegDiff;
        }
    }   
    return max;
}
static int inDegree(Graph g,Vertex v){
    int count = 0;
    for(Vertex i = 0; i < g->nV; i++){
        for(AdjList j = g->edges[i]; j != NULL; j = j -> next){
            if(j -> v == v){
                count++;
            }
        }
    }
    return count;
}
    
static int outDegree(Graph g,Vertex v){
    int count = 0;
    for(AdjList i = g->edges[v]; i != NULL; i = i ->next){
        count++;
    }
    return count;
}

