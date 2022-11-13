// COMP2521 Assignment 2

// Written by:
// Date:

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

#define MAX_URL_LEN 1024

List getCollection();
static void addOutGoingLinks(Graph g,char *urlFile,List urlList,Vertex v);
Graph GetGraph(List urlList);

int main(int argc, char *argv[]) {
    // argc is the number of command-line arguments, which includes the
    // program name
    // // argv is the array of command-line arguments
    // if (argc != 4) {
    //     fprintf(stderr, "Usage: %s dampingFactor diffPR maxIterations\n",
    //             argv[0]);
    //     return EXIT_FAILURE;
    // }

    // Command-line arguments are received as strings. They can be converted
    // to number types using atoi and atof.
    // double d = atof(argv[1]);
    // double diffPR = atof(argv[2]);
    // int maxIterations = atoi(argv[3]);
    List urlList = getCollection();
    Graph g = GetGraph(urlList);
    GraphFree(g);
}

List getCollection(){
    FILE *f = fopen("collection.txt","r");
    char x[MAX_URL_LEN];
    List l = ListNew();
    while (fscanf(f, " %1023s", x) == 1) {
        ListAppend(l,x);
    }
    fclose(f);
    return l;
}

Graph GetGraph(List urlList){
    int nV = ListSize(urlList);
    Graph g = GraphNew(nV);
    Vertex v = 0;
    for(Node n = urlList->head; n != NULL; n = n -> next,v++){ 
        char urlFile[100];
        strcpy(urlFile,n -> s);
        strcat(urlFile,".txt");
        addOutGoingLinks(g,urlFile,urlList,v);
    }
    ListFree(urlList);
    GraphShow(g);
    return g;
}
/*
given a urlfile the function seach for the out going links in the
file and add them as edges to the Vertex v.
*/
static void addOutGoingLinks(Graph g,char *urlFile,List urlList,Vertex v){
    FILE *f = fopen(urlFile,"r");
    char x[1024];
    fseek(f,16,SEEK_CUR);
    bool reachEnd = false;
    while (fscanf(f, " %1023s", x) == 1) {
        if(strcmp(x,"#end") == 0){
            reachEnd = true;
            continue;
        }
        else if(reachEnd == true){
            if(strcmp(x,"Section-1") == 0){
                break;
            }else{
                reachEnd = false;
                Edge e = {v,ListGetIndex(urlList,"#end")};
                if(e.v != e.w)
                GraphInsertEdge(g,e);
            }
        }

    Edge e = {v,ListGetIndex(urlList,x)};
    if(e.v != e.w)
    GraphInsertEdge(g,e);
    }
    fclose(f);
}


