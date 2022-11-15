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

typedef struct pageRank {
    double rank;
    int vertex;
}PR;

List getCollection();
static void addOutGoingLinks(Graph g,char *urlFile,List urlList,Vertex v);
static double caculatePR(double d,Graph g,int n,Vertex v,PR *pr1);
Graph GetGraph(List urlList);
static wIn(Graph g,Vertex v,Vertex u);
static int countInLinks(Graph g,Vertex v);
static double wOut(Graph g, Vertex v, Vertex u);
static int countOutLinks(Graph g,Vertex v);
static void copyPR(PR *pr1,PR *pr2,int n);
static double caculateDiff(PR *pr1,PR *pr2,int n);
void doPageRank(double d,double diffPR,int maxIterations,PR *pr1,int n,Graph g);

int main(int argc, char *argv[]) {
    // argc is the number of command-line arguments, which includes the
    // program name
    // // argv is the array of command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s dampingFactor diffPR maxIterations\n",
                argv[0]);
        return EXIT_FAILURE;
    }
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    List urlList = getCollection();
    Graph g = GetGraph(urlList);
    int n = ListSize(urlList);
    PR pr1[n];
    for(int i = 0; i < n; i++){
        pr1[i].rank = (double)1/(double)n;
        pr1[i].vertex = i;
    }
    doPageRank(d,diffPR,maxIterations,pr1,n,g);
    
    for(int i = 0; i < n; i++){
        char *s = ListGetString(urlList,pr1[i].vertex);
        int outLinks = countOutLinks(g,pr1[i].vertex);
        printf("%s %d %.7lf",s,outLinks,pr1[i].rank);
    }

    
}

static void mergeSort(PR *pr){

}

void doPageRank(double d,double diffPR,int maxIterations,PR *pr1,int n,Graph g){
    int iteration = 0;
    double diff = diffPR;
    while(iteration < maxIterations && diff >= diffPR){
        int t = iteration;
        PR pr2[n]; // for iteration t + 1
        // get the vavlues for t + 1
        for(Vertex v = 0; v < n; v++){
            pr2[v].rank = caculatePR(d,g,n,v,pr1);
            pr2[v].vertex = v;
        }
        diff = caculateDiff(pr1,pr2,n);
        copyPR(pr1,pr2,n);
        iteration++;
    }
}
static double caculateDiff(PR *pr1,PR *pr2,int n){
    double diff;
    for(int i = 0; i < n; i++){
        diff += abs(pr2[i].rank - pr1[i].rank);
    }
    return diff;
}
static void copyPR(PR *pr1,PR *pr2,int n){
    for(int i = 0; i < n; i++){
        double rank = pr2[i].rank;
        pr1[i].rank = rank;
        int vertex = pr2[i].vertex;
        pr1[i].vertex = vertex;
    }
}
static double caculatePR(double d,Graph g,int n,Vertex v,PR *pr1){
    double summation;
    for(Vertex j = 0; j < g->nV; j++){
        if(g->edges[j][v]){
            summation += pr1[j].rank * wOut(g,j,v) * wIn(g,j,v);
        }
    }
    return ((double)1 - d)/n + (d *summation);
}

static wIn(Graph g,Vertex v,Vertex u){
    double denominator;
    for(Vertex w = 0; w < g->nE; w++){
        if(g -> edges[v][w]){
            int inLinks = countInLinks(g,w);
            denominator += (inLinks != 0) ? inLinks : 0.5;
        }
    }
    return (double)countInLinks(g,u);
}

static int countInLinks(Graph g,Vertex v){
    int count = 0;
    for(Vertex w = 0; w < g->nV; w++){
        if(g->edges[w][v]){
           count++;
        }
    }
    return count;
}

static double wOut(Graph g, Vertex v, Vertex u){
    double denominator;
    for(Vertex w = 0; w < g->nV; w++){
        if(g -> edges[v][w]){
            int outLinks = countOutLinks(g,w);
            denominator +=  (outLinks != 0) ? outLinks : 0.5;
        }
    }
    return (double)countOutLinks(g,u)/denominator;
}
static int countOutLinks(Graph g,Vertex v){
    int count = 0;
    for(Vertex w = 0; w < g->nV; w++){
        if(g -> edges[v][w]){
            count++;
        }
    }
    return count;
}
/////////////////////////////// for readData file

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
        char urlFile[MAX_URL_LEN];
        strcpy(urlFile,n -> s);
        strcat(urlFile,".txt");
        addOutGoingLinks(g,urlFile,urlList,v);
    }
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
                if(e.v != e.w){
                    GraphInsertEdge(g,e);
                }
            }
        }
        Edge e = {v,ListGetIndex(urlList,x)};
        if(e.v != e.w){
            GraphInsertEdge(g,e);
        }
    }
    fclose(f);
}


