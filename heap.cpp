#include <iostream>
#include <iomanip>
#include "heap.h"
#include "data_structures.h"
using namespace std;

// Initialize heap
HEAP* init(int capacity) {
    HEAP *heap = new HEAP;  // new heap
    // return NULL if not initialized.
    if (heap == NULL) {
        cout << "Memory allocation failed." << endl;
        return NULL;
    }
    // initializing capacity, size and new element for the heap.
    heap->capacity = capacity;
    heap->size = 0;
    heap->A = new ELEMENT*[capacity];

    // if NULL return error
    if (heap->A == NULL) {
        cout << "Memory allocation failed." << endl;
        delete heap; // delete heap to clear memeory.
        return NULL;
    }
    // adding elements to the heap.
    for (int i = 0; i < capacity; i++) {
        ELEMENT* newElement = new ELEMENT;
        heap->A[i] = newElement; 
    }
    return heap;
}

// build min heap
void buildH(HEAP* heap)
{
    int n = heap->size; // n = size of heap.
    for(int i = (n/2)-1; i>=0; i--)
    {
        heapify(heap, i);   // calling the heapify to maintain min heap.
    }
}

// heapify
void heapify(HEAP* heap, int i)
{
    int min = i;    // initializing min.
    int left = 2 * i + 1;   // left child.
    int right = 2 * i + 2;  // right child.

    if(left < heap->size && heap->A[left]->key < heap->A[min]->key)
    {
        min = left; // if left<min, then min = left
    }
    if(right < heap->size && heap->A[right]->key < heap->A[min]->key)
    {
        min = right;    // if right<min, then min = right
    }
    if(min != i)    // if minimum value changes, then we swap it with i.
    {
        // Swapping A[i] and A[min]
        ELEMENT* temp = heap->A[i];  // temporary holder temp.
        heap->A[i] = heap->A[min];
        heap->A[min] = temp;
        heapify(heap, min);  // calling heapify to maintain min heap property.
    }
}

// insert in heap
void insertH(HEAP* heap, VERTEX* pVertex)
{
    // If heap is NULL return error.
    if(heap == NULL)
    {
        cout << "Error: heap is NULL" << endl;
        return;
    }
    // If the size of heap excedes its capacity then return.
    if(heap->size >= heap->capacity)
    {
        return;
    }
    
    heap->A[heap->size] = pVertex;  // add new key at the end of the heap.
    int i = heap->size;  // set i.
    heap->size++;   // increment size to incorporate new element.
    
    // rearranging to maintain min heap property.
    while (i > 0 && heap->A[(i-1)/2]->key > heap->A[i]->key) {
        // swapping A[i] with A[(i-1)/2] or child with parent.
        ELEMENT* temp = heap->A[i];  // temporary holder temp.
        heap->A[i] = heap->A[(i-1)/2];
        heap->A[(i-1)/2] = temp;

        i = (i-1)/2; // updating i.
    }
}

// ExtractMin - get minimum value from the heap     // This code is updated to correctly return vertex
pVertex extractMin(HEAP* heap)
{
    // if heap is NULL return error.
    if(heap == NULL)
    {
        cout << "Error: heap is NULL" << endl;
        return NULL;
    }
    // if heap size is < 0 return.
    if(heap->size <= 0)
    {
        return NULL;
    }
    // Save the vertex with the minimum key value
    pVertex minVertex = heap->A[0];

    // Replace the root of the heap with the last element
    heap->A[0] = heap->A[heap->size - 1];
    heap->size--; // Decrease the size of the heap
    heapify(heap, 0); // Call heapify to maintain the min-heap property from the root

    return minVertex; // Return the vertex with the minimum key
}

//Decrease key value
void decreaseKey(HEAP* heap, int i, double newKey)
{
    // if heap is NULL return error.
    if(heap == NULL)
    {
        cout << "Error: heap is NULL" << endl;
        return;
    }
    // if heap size is equal to 0 then return.
    if(heap->size == 0)
    {
        return;
    }
    i--;  // decrementing i.
    // checking range of i and returning if new key of greater than original key.
    if(i<0 && i>heap->size || heap->A[i]->key < newKey)
    {
        return;
    }
    // changing the vakue of key.
    heap->A[i]->key = newKey;
    // rearranging to maintain min heap property.
    while(i != 0 && heap->A[(i-1)/2]->key > heap->A[i]->key) {
        // swapping A[i] with A[(i-1)/2] or child with parent.
        ELEMENT* temp = heap->A[i];  // temporary holder temp.
        heap->A[i] = heap->A[(i-1)/2];
        heap->A[(i-1)/2] = temp;

        i = (i-1)/2; // updating i.
    }
}

// Printing heap
void printH(HEAP* heap)
{
    // if NULL return error.
    if(heap == NULL)
    {
        cout << "Error: heap is NUll" << endl;
        return;
    }
    // if not then print the contents of heap.
    else
    {
        fprintf(stdout, "%d", heap->size);  // size of heap.
        for(int i = 0; i < heap->size; i++)
        {
            fprintf(stdout, "\n");
            fprintf(stdout, "%lf", heap->A[i]->key);
        }
    }
}