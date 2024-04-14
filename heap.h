#ifndef _heap_cpp
#define _heap_cpp
#include "data_structures.h"

extern int heapifycalls;
void buildH(HEAP* h,int n);
void heapify(HEAP*,int);
pVertex extractMin(HEAP* h);
void decreaseKey(HEAP*,int,double);
void insertH(HEAP*,pVertex);
void printH(HEAP*);

#endif