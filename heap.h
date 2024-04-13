#ifndef heap_h
#define heap_h 1
#include "data_structures.h"

HEAP* init(int capacity);   // initialize a new heap.
void buildH(HEAP* heap);    // build heap
void heapify(HEAP* heap, int i);    // heapify - arrange elements in order as min heap.
void insertH(HEAP* heap, VERTEX* pVertex);   // insert element in heap
VERTEX* extractMin(HEAP* heap);    // get minimum value from the heap.
void decreaseKey(HEAP* heap, int i, double newKey);    // decrease key.
void printH(HEAP* heap);    // print heap.

#endif
