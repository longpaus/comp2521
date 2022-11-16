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
static double wIn(Graph g,Vertex v,Vertex u);
static int countInLinks(Graph g,Vertex v);
static double wOut(Graph g, Vertex v, Vertex u);
static int countOutLinks(Graph g,Vertex v);
static void copyPR(PR *pr1,PR *pr2,int n);
static double caculateDiff(PR *pr1,PR *pr2,int n);
void doPageRank(double d,double diffPR,int maxIterations,PR *pr1,int n,Graph g);
static void order(PR *pr,int n);


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
    order(pr1,n);
    for(int i = 0; i < n; i++){
        char *s = ListGetString(urlList,pr1[i].vertex);
        int outLinks = countOutLinks(g,pr1[i].vertex);
        printf("%s %d %.7lf\n",s,outLinks,pr1[i].rank);
    }
    ListFree(urlList);
    GraphFree(g);

    
}
//sort the given PR
static void order(PR *pr,int n){
    double tempRank;
    int tempVertex;
    for (int i = 0; i < n; i++) {     
        for (int j = i+1; j < n; j++) {     
           if(pr[i].rank < pr[j].rank) {    
               tempRank = pr[i].rank;
               tempVertex = pr[i].vertex;    
               pr[i].rank = pr[j].rank;
               pr[i].vertex = pr[j].vertex;    
               pr[j].rank = tempRank;
               pr[j].vertex = tempVertex;    
           }     
        }     
    }    

}

//given a graph g return the pagerank for each vertex
void doPageRank(double d,double diffPR,int maxIterations,PR *pr1,int n,Graph g){
    int iteration = 0;
    double diff = diffPR;
    while(iteration < maxIterations && diff >= diffPR){
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
//caculate diff given pr1 and pr2
static double caculateDiff(PR *pr1,PR *pr2,int n){
    double diff = 0.0;
    for(int i = 0; i < n; i++){
        diff += fabs(pr2[i].rank - pr1[i].rank);
    }
    return diff;
}
//copy pr2 into pr1
static void copyPR(PR *pr1,PR *pr2,int n){
    for(int i = 0; i < n; i++){
        double rank = pr2[i].rank;
        pr1[i].rank = rank;
        int vertex = pr2[i].vertex;
        pr1[i].vertex = vertex;
    }
}

//caculate the pagerank for a specific vertex
static double caculatePR(double d,Graph g,int n,Vertex v,PR *pr1){
    double summation = 0.0;
    for(Vertex j = 0; j < g->nV; j++){
        if(g->edges[j][v]){
            double out =  wOut(g,j,v);
            double in = wIn(g,j,v);
            summation += pr1[j].rank * in * out;
        }
    }
    return ((double)1 - d)/(double)n + (d *summation);
}

//cacualte the Win from vertex v to u
static double wIn(Graph g,Vertex v,Vertex u){
    double denominator = 0.0;
    for(Vertex w = 0; w < g->nV; w++){
        if(g -> edges[v][w]){
            int inLinks = countInLinks(g,w);
            denominator += (double)inLinks;
        }
    }
    return (double)countInLinks(g,u)/denominator;
}

//given vertex v return how manny in going links it has 
// in graph g
static int countInLinks(Graph g,Vertex v){
    int count = 0;
    for(Vertex w = 0; w < g->nV; w++){
        if(g->edges[w][v]){
           count++;
        }
    }
    return count;
}
//caulate the Wout from vertex v to u
static double wOut(Graph g, Vertex v, Vertex u){
    double denominator = 0.0;
    int outLinks;
    for(Vertex w = 0; w < g->nV; w++){
        if(g -> edges[v][w]){
            outLinks = countOutLinks(g,w);
            denominator +=  (outLinks != 0) ? (double)outLinks : 0.5;
        }
    }
    outLinks = countOutLinks(g,u);
    double numerator = (outLinks != 0) ? (double)outLinks : 0.5;
    return numerator/denominator;
}

//given vertex v return how manny out going links it has 
// in graph g
static int countOutLinks(Graph g,Vertex v){
    int count = 0;
    for(Vertex w = 0; w < g->nV; w++){
        if(g -> edges[v][w]){
            count++;
        }
    }
    return count;
}
/////////////////////////////// for readData 

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
    return g;
}
/*
given a urlfile the function seach for the out going links in the
file and add them as edges to the Vertex v.
*/
static void addOutGoingLinks(Graph g,char *urlFile,List urlList,Vertex v){
    FILE *f = fopen(urlFile,"r");
    bool collectUrl = false;
    char x[1024];
    while (fscanf(f, " %1023s", x) == 1) {
        if(strcmp(x,"Section-1") == 0){
           collectUrl = true;
           continue;
        }
        if(strcmp(x,"#end") == 0){
            break;
        }
        if(collectUrl){
            Edge e = {v,ListGetIndex(urlList,x)};
            if(e.v != e.w){
                GraphInsertEdge(g,e);
            }
        }
       
    }
    fclose(f);
}


