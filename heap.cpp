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
    heap->capacity = capacity;
    heap->size = 0;
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
    int n = heap->size;
    int min = i;    // initializing min.
    int left = 2 * i + 1;   // left child.
    int right = 2 * i + 2;  // right child.

    if(left < n)
    {
        if(heap->A[left]->key < heap->A[min]->key)
        {
            min = left;
        }
    }

    if(right < n)
    {
        if(heap->A[right]->key < heap->A[min]->key)
        {
            min = right;
        }
    }

    if(min != i)    // if minimum value changes, then we swap it with i.
    {
        // Swapping A[i] and A[min]
        ELEMENT* temp = heap->A[i];  // temporary holder temp.
        heap->A[i] = heap->A[min];
        heap->A[min] = temp;
        heapify(heap, min);  // calling heapify to maintain min heap property.
    }

    for(int i = 0; i < heap->size; i++)
    {
        heap->A[i]->position = i;
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
    if(heap->size == heap->capacity)
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
VERTEX* extractMin(HEAP* heap)
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
    VERTEX* minVertex = heap->A[0];

    // Replace the root of the heap with the last element
    heap->A[0] = heap->A[heap->size - 1];
    heap->size--; // Decrease the size of the heap

    if(heap->size > 0)
    {
        heapify(heap, 0);
    }

    return minVertex; // Return the vertex with the minimum key
}

void decreaseKey(HEAP* heap, int id, double newKey)
{
    // Check if the heap pointer is valid.
    if (heap == NULL) {
        cout << "Error: heap is NULL" << endl;
        return;
    }

    // Check if the heap size is valid for operation.
    if (heap->size <= 0) {
        cout << "Error: heap size is zero" << endl;
        return;
    }

    // Check if the index is within the bounds of the heap array.
    if (id < 0 || id >= heap->size) {
        cout << "Error: invalid index in DecreaseKey - " << id << " out of bounds [0, " << heap->size - 1 << "]" << endl;
        return;
    }

    // Check if the new key is actually smaller than the current key.
    if (heap->A[id]->key <= newKey) {
        cout << "Error: new key is not smaller than the current key" << endl;
        return;
    }

    // Update the key of the vertex.
    heap->A[id]->key = newKey;

    // Bubble up the element to restore the heap property if necessary.
    int current = id;
    while (current > 0) {
        int parentIndex = (current - 1) / 2;
        if (heap->A[parentIndex]->key > heap->A[current]->key) {
            // Swapping the current element with its parent.
            pVertex temp = heap->A[current];
            heap->A[current] = heap->A[parentIndex];
            heap->A[parentIndex] = temp;

            // Update current index to parent index after swap.
            current = parentIndex;
        } else {
            // If the parent's key is not greater, the heap property is restored.
            break;
        }
    }
}



// //Decrease key value
// void decreaseKey(HEAP* heap, int id, double newKey)
// {
    
//     // if heap is NULL return error.
//     if(heap == NULL)
//     {
//         cout << "Error: heap is NULL" << endl;
//         return;
//     }
//     // if heap size is equal to 0 then return.
//     // if(heap->size <= 0)
//     // {
//     //     return;
//     // }

//     id--;

//     if (heap->size == 0 || id >= heap->size || id < 0) {
//         cout << "Error: invalid call to DecreaseKey" << endl;
//         return;
//     }

//     heap->A[id]->key = newKey;

//     // rearranging to maintain min heap property.
//     while(id != 0 && heap->A[(id-1)/2]->key > heap->A[id]->key) {
//         // swapping A[i] with A[(i-1)/2] or child with parent.
//         pVertex temp = heap->A[id];  // temporary holder temp.
//         heap->A[id] = heap->A[(id-1)/2];
//         heap->A[(id-1)/2] = temp;

//         id = (id-1)/2; // updating i.
//     }
// }

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