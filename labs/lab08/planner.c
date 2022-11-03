// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Place.h"
#include "PQ.h"

////////////////////////////////////////////////////////////////////////
// Your task
static void addAdjacentNodeToPQ(Place cities[],int numCities,Vertex v,PQ pq,int *dist,Vertex *pred);
static double getDistance(int x1,int y1,int x2,int y2);

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(Place cities[], int numCities, Place powerPlant,
              PowerLine powerLines[]) {
    int dist[numCities];
    Vertex pred[numCities];
    Vertex src = -1;
    for(Vertex i = 0; i < numCities; i++){
        dist[i] = 999;
        pred[i] = -1;
        if(strcmp(cities[i].name,powerPlant.name) == 0){
            src = i;
        }
    }
    dist[src] = 0;
    PQ pq = PQNew();
    addAdjacentNodeToPQ(cities,numCities,src,pq,dist,pred);
    while(!PQIsEmpty(pq)){
        Edge u = PQExtract(pq);
        addAdjacentNodeToPQ(cities,numCities,u.w,pq,dist,pred);
    }
    for(int i = 0; i < numCities; i++){
        if(i != src){
            Place p1 = {cities[i].x,cities[i].y};
            Place p2 = {cities[pred[i]].x,cities[pred[i]].y};
            PowerLine pl = {p1,p2};
            powerLines[i] = pl;
        }
    }


    return numCities;
}
static void addAdjacentNodeToPQ(Place cities[],int numCities,Vertex v,PQ pq,int *dist,Vertex *pred){
    for(Vertex w = 0; w < numCities; w++){
        if(w != v){
            Place edgeV = cities[v];
            Place edgeW = cities[w];
            double vToW = getDistance(edgeV.x,edgeV.y,edgeW.x,edgeW.y);
            Edge e = {v,w,vToW};
            PQInsert(pq,e);
            //get dist from w to src in the current path.
            double wToSrc = dist[v] + vToW;
            if(wToSrc < dist[w]){
                dist[w] = wToSrc;
                pred[w] = v;
            }
        }
    }
}

static double getDistance(int x1,int y1,int x2,int y2){
    return sqrt(pow((double)(x1 - x2),2) + pow((double)(y1 - y2),2));
}
////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(Place cities[], int numCities,
              Place powerPlants[], int numPowerPlants,
              PowerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
