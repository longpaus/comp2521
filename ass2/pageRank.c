// COMP2521 Assignment 2

// Written by:Long Pham Hoang
// Date: 16/11/22

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"
#include "ReadData.h"


typedef struct pageRank {
	double weight;
	int vertex;
} PR;


static double caculatePR(double d, Graph g, int n, Vertex v, PR *pr1);
Graph GetGraph(List urlList);
static double wIn(Graph g, Vertex v, Vertex u);
static int countInLinks(Graph g, Vertex v);
static double wOut(Graph g, Vertex v, Vertex u);
static int countOutLinks(Graph g, Vertex v);
static void copyPR(PR *pr1, PR *pr2, int n);
static double caculateDiff(PR *pr1, PR *pr2, int n);
void doPageRank(double d, double diffPR, int maxIterations, PR *pr1, int n,
                Graph g);
static void sortByWeight(PR *pr, int n);
static void sortByName(PR *pr, int lo, int hi,List urlList);
static void order(PR *pr, int n,List urlList);

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
	for (int i = 0; i < n; i++) {
		pr1[i].weight = (double)1 / (double)n;
		pr1[i].vertex = i;
	}
	doPageRank(d, diffPR, maxIterations, pr1, n, g);
	order(pr1,n,urlList);
	for (int i = 0; i < n; i++) {
		char *s = ListGetString(urlList, pr1[i].vertex);
		int outLinks = countOutLinks(g, pr1[i].vertex);
		printf("%s %d %.7lf\n", s, outLinks, pr1[i].weight);
	}
	ListFree(urlList);
	GraphFree(g);
	return 0;
}
static void order(PR *pr, int n,List urlList){
	sortByWeight(pr, n);
	int hi = 0;
	int lo = 0;
	while (hi < n) {
		while (hi < n && pr[lo].weight == pr[hi].weight) {
			hi++;
		}
		sortByName(pr,lo, hi - 1,urlList);
		lo = hi;
	}
}

static void sortByName(PR *pr, int lo, int hi,List urlList) {
	for (int i = lo; i <= hi; ++i) {
		for (int j = i + 1; j <= hi; ++j) {
			char *s1 = ListGetString(urlList, pr[i].vertex);
			char *s2 = ListGetString(urlList, pr[j].vertex);
			if (strcmp(s1,s2) > 0) {
				PR tmp = pr[i];
				pr[i] = pr[j];
				pr[j] = tmp;
			}
		}
	}
}
//sort the given PR by their weight
static void sortByWeight(PR *pr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (pr[i].weight < pr[j].weight) {
				PR tmp = pr[i];
				pr[i] = pr[j];
				pr[j] = tmp;
			}
		}
	}
}

//given a graph g return the pagerank for each vertex
void doPageRank(double d, double diffPR, int maxIterations, PR *pr1, int n,
                Graph g) {
	int iteration = 0;
	double diff = diffPR;
	while (iteration < maxIterations && diff >= diffPR) {
		PR pr2[n];  // for iteration t + 1
		// get the vavlues for t + 1
		for (Vertex v = 0; v < n; v++) {
			pr2[v].weight = caculatePR(d, g, n, v, pr1);
			pr2[v].vertex = v;
		}
		diff = caculateDiff(pr1, pr2, n);
		copyPR(pr1, pr2, n);
		iteration++;
	}
}
//caculate diff given pr1 and pr2
static double caculateDiff(PR *pr1, PR *pr2, int n) {
	double diff = 0.0;
	for (int i = 0; i < n; i++) {
		diff += fabs(pr2[i].weight - pr1[i].weight);
	}
	return diff;
}
//copy pr2 into pr1
static void copyPR(PR *pr1, PR *pr2, int n) {
	for (int i = 0; i < n; i++) {
		double rank = pr2[i].weight;
		pr1[i].weight = rank;
		int vertex = pr2[i].vertex;
		pr1[i].vertex = vertex;
	}
}

//caculate the pagerank for a specific vertex
static double caculatePR(double d, Graph g, int n, Vertex v, PR *pr1) {
	double summation = 0.0;
	for (Vertex j = 0; j < g->nV; j++) {
		if (g->edges[j][v]) {
			double out = wOut(g, j, v);
			double in = wIn(g, j, v);
			summation += pr1[j].weight * in * out;
		}
	}
	return ((double)1 - d) / (double)n + (d * summation);
}

//cacualte the Win from vertex v to u
static double wIn(Graph g, Vertex v, Vertex u) {
	double denominator = 0.0;
	for (Vertex w = 0; w < g->nV; w++) {
		if (g->edges[v][w]) {
			int inLinks = countInLinks(g, w);
			denominator += (double)inLinks;
		}
	}
	return (double)countInLinks(g, u) / denominator;
}

//given vertex v return how manny in going links it has
// in graph g
static int countInLinks(Graph g, Vertex v) {
	int count = 0;
	for (Vertex w = 0; w < g->nV; w++) {
		if (g->edges[w][v]) {
			count++;
		}
	}
	return count;
}
//caulate the Wout from vertex v to u
static double wOut(Graph g, Vertex v, Vertex u) {
	double denominator = 0.0;
	int outLinks;
	for (Vertex w = 0; w < g->nV; w++) {
		if (g->edges[v][w]) {
			outLinks = countOutLinks(g, w);
			denominator += (outLinks != 0) ? (double)outLinks : 0.5;
		}
	}
	outLinks = countOutLinks(g, u);
	double numerator = (outLinks != 0) ? (double)outLinks : 0.5;
	return numerator / denominator;
}

//given vertex v return how manny out going links it has
// in graph g
static int countOutLinks(Graph g, Vertex v) {
	int count = 0;
	for (Vertex w = 0; w < g->nV; w++) {
		if (g->edges[v][w]) {
			count++;
		}
	}
	return count;
}
