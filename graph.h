#ifndef _graph_cpp
#define _graph_cpp 1
#include "data_structures.h"

void initSingleSource(pVertex* V, int vertices, int source);
bool relax(pVertex start, pVertex end, double weight);
void singleSource(pVertex* V, int vertices, int vSource, pEDGE* adjList);

void initSinglePair(pVertex* V, int num, int source, int destination);
void printlength(int s, int t);
void printPath(int s, int t);

#endif