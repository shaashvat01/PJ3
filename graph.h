// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: It is the header file for graph.cpp, it contains function declaration for graph.cpp;

#ifndef graph_h
#define graph_h 1
#include "data_structures.h"

// global declaration.
extern int recent_source;
extern int recent_destination;

void initSingleSource(pVertex* V, int vertices, int source); // initializing single source
bool relax(pVertex start, pVertex end, double weight); // function to relax the edges
void singleSource(pVertex* V, int vertices, int vSource, pEDGE* adjList, int destination); // Djiskistra
void initSinglePair(pVertex* V, int num, int source, int destination); // initialize single pair
void printlength(int s, int t); // print length
void printPath(int source,int target); // print path

#endif