#include "heap.h"
#include "data_structures.h"
#include <iostream>
#include "math.h"
using namespace std;

// heapifycalls for counting number of heapify calls
int  heapifycalls = 0;

void heapify(HEAP* h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if left child is smaller than parent
    if (left < h->size && h->A[left]->key < h->A[smallest]->key) {
        smallest = left;
    }

    // Check if right child is smaller than smallest so far
    if (right < h->size && h->A[right]->key < h->A[smallest]->key) {
        smallest = right;
    }

    // If smallest is not the root
    if (smallest != i) {
        // Swap vertices
        pVertex temp = h->A[i];
        int temp_heappos = h->A[i]->h_pos;

        h->A[i] = h->A[smallest];
        h->A[i]->h_pos = temp_heappos;

        h->A[smallest] = temp;
        h->A[smallest]->h_pos = smallest;

        // Recursively heapify the affected subtree
        heapify(h, smallest);
    }
}

void buildH(HEAP* h, int n){
    int i = n/2-1;
    for(int r = i;r>=0;r--){
        heapify(h,r);
        heapifycalls++;
    }
}

pVertex extractMin(HEAP* h) {
    if (h == NULL) {
        cout << "Error: heap is Null";
        return NULL;
    }
    if (h->size <= 0) {
        fprintf(stdout, "Error: heap is empty");
        return NULL;
    }
    pVertex minVertex = h->A[0];
    h->size = h->size - 1;
    h->A[0] = h->A[h->size]; // Replace the root with the last element
    h->A[0]->h_pos = 0; // Update heappos for the root vertex
    heapify(h, 0); // Heapify the heap from the root

    fprintf(stdout,"ExtractMin: %d", minVertex->id);
    return minVertex;
}

void decreaseKey(HEAP* h, int position, double newKey) {
    int i = position;

    if (h == NULL) {
        return; // heap is NULL
    }

    if (h->size == 0 || i >= h->size || i < 0) {
        return; // invalid call to decrease key
    }

    if (newKey > h->A[i]->key) {
        return; // new key not smaller than current key
    }

    h->A[i]->key = newKey;
    while (i != 0 && h->A[(i - 1) / 2]->key > h->A[i]->key) {
        // Swap vertices
        pVertex temp = h->A[i];
        int temp_heappos = h->A[i]->h_pos;

        h->A[i] = h->A[(i - 1) / 2];
        h->A[i]->h_pos = temp_heappos;

        h->A[(i - 1) / 2] = temp;
        h->A[(i - 1) / 2]->h_pos = (i - 1) / 2;

        i = (i - 1) / 2;
    }
}

void insertH(HEAP* h, pVertex newKey) {
    if (h->capacity == 0) {
        return;  // heap i sempty
    }
    if (h->size == h->capacity) {
        return; // heap is full
    } 

    if (h->A[0] == NULL) fprintf(stdout, "0 is NULL.");

    h->A[h->size] = newKey;
    newKey->h_pos = h->size; // Set heappos for the new vertex
    h->size++;
    int i = h->size - 1;
    while (i > 0 && h->A[(i - 1) / 2]->key > h->A[i]->key) {
        // Swap vertices
        pVertex temp = h->A[i];
        int temp_heappos = h->A[i]->h_pos;

        h->A[i] = h->A[(i - 1) / 2];
        h->A[i]->h_pos = temp_heappos;

        h->A[(i - 1) / 2] = temp;
        h->A[(i - 1) / 2]->h_pos = (i - 1) / 2;

        i = (i - 1) / 2;
    }
    return ;
}

void printH(HEAP* h) {
    if (h == NULL) {
        fprintf(stdout, "heap is empty .\n");
        return; //cout<<"Error: heap is NUll"<<endl;
    } 
    for (int i = 0; i < h->size; i++) {
        fprintf(stdout,"index : %d, heappos: %d, Distance :%lf\n", h->A[i]->id, h->A[i]->h_pos,h->A[i]->key);
    }
}
