// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: heap.cpp contains major functionality of the heaps. It includes functions to build, heapify,
// insert, extractMin, decreaseKey, initialize and print the heap. These functions are important for the proper
// execution of the code.

#include "heap.h"
#include "data_structures.h"
#include "math.h"
#include <iostream>
using namespace std;

// count1 for counting number of heapify calls
int  count1 = 0;

// Initialize heap
HEAP* init(int capacity) 
{
    HEAP *heap = new HEAP;  // new heap
    // return NULL if not initialized.
    if (heap == NULL) 
    {
        cout << "Memory allocation failed." << endl;
        return NULL;
    }
    // initializing capacity, size and new element for the heap.
    heap->capacity = capacity;
    heap->size = 0;
    heap->A = new ELEMENT*[capacity];

    // if NULL return error
    if (heap->A == NULL) 
    {
        cout << "Memory allocation failed." << endl;
        delete heap; // delete heap to clear memeory.
        return NULL;
    }
    // adding elements to the heap.
    for (int i = 0; i < capacity; i++) 
    {
        ELEMENT* newElement = new ELEMENT;
        heap->A[i] = newElement; 
    }
    return heap;
}

// build min heap
void buildH(HEAP* heap, int size)
{
    int n = (size/2)-1; // size of the heap
    for(int i = n; i >= 0; i--)
    {
        heapify(heap,i); // calling heapify to maintain the heap property.
        count1++; // iterating count everytime heap is called.
    }
}

// heapify
void heapify(HEAP* heap, int i) 
{
    int min = i;  // initializing min
    int left = 2 * i + 1; // left child.
    int right = 2 * i + 2; // right child.

    if (left < heap->size && heap->A[left]->key < heap->A[min]->key) 
    {
        min = left; // if left < min, then min = left.
    }
    if (right < heap->size && heap->A[right]->key < heap->A[min]->key) 
    {
        min = right;  // if right < min, then min = right.
    }
    if (min != i) // if min value changes then we swap it with i.
    { 
        // S A[i] and A[min]/ vertices
        pVertex temp = heap->A[i]; // temperorary vertex
        int temp_heap = heap->A[i]->h_pos; 

        heap->A[i] = heap->A[min];
        heap->A[i]->h_pos = temp_heap;

        heap->A[min] = temp;
        heap->A[min]->h_pos = min;

        heapify(heap, min); // calling heapify to maintain the heap property.
    }
}

// insert in Heap.
void insertH(HEAP* heap, pVertex key) 
{
    // if heap is return.
    if (heap->capacity == 0) 
    {
        return;  
    }
    // if heap is full or has reached its capacity then return.
    if (heap->size == heap->capacity) 
    {
        return;
    } 

    heap->A[heap->size] = key; // add new key at the end of the heap.
    key->h_pos = heap->size; // setting position of hrap for new vertex.
    heap->size++; // incrementing size
    int i = heap->size - 1; // set i.

    // rearranging to maintain heap property.
    while (i > 0 && heap->A[(i - 1) / 2]->key > heap->A[i]->key) {
        // Swapping A[i] with A[(i-1)/2] or child with parent.
        pVertex temp = heap->A[i];
        int temp_heap = heap->A[i]->h_pos;

        heap->A[i] = heap->A[(i - 1) / 2];
        heap->A[i]->h_pos = temp_heap;

        heap->A[(i - 1) / 2] = temp;
        heap->A[(i - 1) / 2]->h_pos = (i - 1) / 2;

        i = (i - 1) / 2;
    }
    return ;
}

// extractMin - get the minimum value from the heap.
pVertex extractMin(HEAP* heap) 
{
    // if heap is NULL return.
    if (heap == NULL) 
    {
        return NULL;
    }
    // if heap size is < 0 return.
    if (heap->size <= 0) 
    {
        return NULL;
    }
    pVertex min = heap->A[0];  // initializing min to node.
    heap->size --; // decrementing size
    heap->A[0] = heap->A[heap->size]; // adjusting values
    heap->A[0]->h_pos = 0;
    heapify(heap, 0); // heapify to maintain the heap property.

    return min;  // returning the minimum value.
}

void decreaseKey(HEAP* heap, int i, double key) 
{
    // if heap is NULL return.
    if (heap == NULL) 
    {
        return;
    }
    // if heap size is 0 then return.
    if (heap->size == 0) 
    {
        return; 
    }
    // if i is bigger then the size or is negative value, then return.
    if(i >= heap->size || i < 0)
    {
        return;
    }
    // if new key is not smaller then the current key, then return.
    if (key > heap->A[i]->key) 
    {
        return; 
    }
    // changing the value of key.
    heap->A[i]->key = key;
    // rearranging to maintain the heap property.
    while (i != 0 && heap->A[(i - 1) / 2]->key > heap->A[i]->key) 
    {
        // swapping A[i] with A[(i-2)/2] or child with parent.
        pVertex temp = heap->A[i];
        int temp_heap = heap->A[i]->h_pos;

        heap->A[i] = heap->A[(i - 1) / 2];
        heap->A[i]->h_pos = temp_heap;

        heap->A[(i - 1) / 2] = temp;
        heap->A[(i - 1) / 2]->h_pos = (i - 1) / 2;

        i = (i - 1) / 2;
    }
}

void printH(HEAP* heap) {
    // if NULL return.
    if (heap == NULL) {
        return; 
    } 
    // printing heap
    for (int i = 0; i < heap->size; i++) {
        fprintf(stdout,"index : %d, heappos: %d, Distance :%lf\n", heap->A[i]->id, heap->A[i]->h_pos,heap->A[i]->key);
    }
}