
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Graph.h"
#include "List.h"

#define MAX_URL_LEN 100

static void addOutGoingLinks(Graph g, char *urlFile, List urlList, Vertex v);


List getCollection() {
	FILE *f = fopen("collection.txt", "r");
	char x[MAX_URL_LEN];
	List l = ListNew();
	while (fscanf(f, " %1023s", x) == 1) {
		ListAppend(l, x);
	}
	fclose(f);
	return l;
}

Graph GetGraph(List urlList) {
	int nV = ListSize(urlList);
	Graph g = GraphNew(nV);
	Vertex v = 0;
	for (Node n = urlList->head; n != NULL; n = n->next, v++) {
		char urlFile[MAX_URL_LEN + 4];
		strcpy(urlFile, n->s);
		strcat(urlFile, ".txt");
		addOutGoingLinks(g, urlFile, urlList, v);
	}
	return g;
}
/*
given a urlfile the function seach for the out going links in the
file and add them as edges to the Vertex v.
*/
static void addOutGoingLinks(Graph g, char *urlFile, List urlList, Vertex v) {
	FILE *f = fopen(urlFile, "r");
	bool collectUrl = false;
	char x[100];
	while (fscanf(f, " %99s", x) == 1) {
		if (strcmp(x, "Section-1") == 0) {
			collectUrl = true;
			continue;
		}
		if (strcmp(x, "#end") == 0) {
			break;
		}
		if (collectUrl) {
			Edge e = {v, ListGetIndex(urlList, x)};
			if (e.v != e.w) {
				GraphInsertEdge(g, e);
			}
		}
	}
	fclose(f);
}


