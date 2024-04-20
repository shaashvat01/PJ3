// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: It is the header file for heap.cpp, it contains function declaration for heap.cpp;

#ifndef heap_h
#define heap_h 1
#include "data_structures.h"

extern int count1;

HEAP* init(int capacity);   // initialize a new heap.
void buildH(HEAP* heap, int size); // build heap.
void heapify(HEAP* heap, int i); // heapify - arrange elements in order as min heap.
void insertH(HEAP* heap, pVertex key); // insert element in heap.
pVertex extractMin(HEAP* heap); // get minimum value from the heap.
void decreaseKey(HEAP* heap, int i, double key); // decrease key.
void printH(HEAP* heap); // print heap.

#endif