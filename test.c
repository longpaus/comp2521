#define MAX_NODES 100
bool visited[MAX_NODES];

bool dfsCycleCheck(Graph g, int nV, Vertex v, Vertex u) {
   visited[v] = true;
   Vertex w;
   for (w = 0; w < nV; w++) {
      if (adjacent(g, v, w)) {
         if (!visited[w])
            return dfsCycleCheck(g, nV, w, v);
         else if (w != u)
            return true;
      }
   }
   return false;
}

Graph kruskal(Graph g, Edge sortedEdges[], int nV, int nE) {
   Graph mst = newGraph(nV);
   
   int n = 0;
   int i;
   for (i = 0; i < nE && n < nV-1; i++) {
      Edge e = sortedEdges[i];
      insertEdge(mst, e);
      n++;
      Vertex v;
      for (v = 0; v < nV; v++)
	 visited[v] = false;
      if (dfsCycleCheck(mst, nV, e.v, e.v)) {    // cycle through node e.v?
	 removeEdge(mst, e);
	 n--;
      }
   }
   return mst;
}
