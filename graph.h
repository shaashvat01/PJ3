#ifndef graph_h
#define graph_h 1
#include "data_structures.h"

// dijistkra - single source(find shortest path), single pair (specific source to specific destination)

// singlesource - adj list, vertex, heap, number of vertices, index of the source
//void singleSource(VERTEX* pVertex, EDGE* pEdge, HEAP *pHEAP, int vertices, int source);
void initSingleSource(pVertex* V, int vertices, int source);
void relax(pVertex u, pVertex v, double w);
void singleSource(pVertex* V, int vertices, int source, pEdge* adjList); 

// single pair - additional for destination
void singlePair(VERTEX* pVertex, EDGE* pEdge, HEAP *pHEAP, int vertices, int source, int destination);

// print - length and shortest path


#endif