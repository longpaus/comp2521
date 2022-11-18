

#ifndef READDATA_H
#define READDATA_H

#include "List.h"
#include "Graph.h"

//get a List of urls from the collection.txt file and return it
List getCollection();


// given a list of url go to every url file and update it's
// outgoing links to a graph and return the graph
Graph GetGraph(List urlList);


#endif
