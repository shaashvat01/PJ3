#include <iostream>
#include <iomanip>
#include "graph.h"
#include "heap.h"
using namespace std;

void initSingleSource(pVertex* V, int vertices, int source) {
    // Initialize single source for Dijkstra's algorithm
    cout << "Inside init" << endl;
    for (int i = 1; i <= vertices; ++i) {
        cout << "Inside for loop of init" << endl;
        V[i]->key = INFINITY; // Set initial key values to infinity
        V[i]->pi = -1; // Set initial predecessor to NIL
    }
    V[source]->key = 0; // Set key of source vertex to 0
}

// u and v are pointers to the vertex and w is the weight of the edge between them.
void relax(pVertex u, pVertex v, double w)
{
    if(v->key > u->key + w)
    {
        v->key = u->key + w; // vertex is updated to new value
        v->pi = u->id; // predecessor of v is to the id of u
    }
}

void singleSource(pVertex* V, int vertices, int source, pEdge* adjList)
{
    cout << "Entering SingleSource function." << endl;
    initSingleSource(V, vertices, source);
    printf("%s","h");

    HEAP* heap = init(vertices); // priority queue - min heap
    if(heap == NULL)
    {
        cout << "Priority Queue not initialized." << endl;
        return;
    }

    for(int i = 1; i <= vertices; i++)
    {
        double key;
        if(i == source)
        {
            key = 0;
        }
        else
        {
            key = INFINITY;
        }
        insertH(heap, key);
        printf("%d", V[i]->id);
        V[i]->position = i - 1; 
    }
    buildH(heap);

    while(heap->size > 0)
    {
        pVertex u = extractMin(heap);
        printf("%d", u->id);
        if(u == NULL)
        {
            break;
        }
        for(pEdge edg = adjList[u->id]; edg != NULL; edg = edg->next)
        {
            pVertex v = V[edg->v];
            if(v->key > u->key + edg->w)
            {
                relax(u,v,edg->w);
                decreaseKey(heap, v->position, v->key);
            }
        }
    }
    // Clean up
    for (int i = 0; i < heap->capacity; i++) {
        delete heap->A[i];
    }
    delete[] heap->A;
    delete heap;
}

void initSinglePair(pVertex* V, int n, int source, int destination) {
    for (int i = 1; i <= n; i++) {
        if (i == source) {
            V[i]->key = 0; // Set key of source vertex to 0
        } else {
            V[i]->key = INFINITY; // Set initial key values to infinity
        }
        V[i]->pi = -1; // Set initial predecessor to NIL
    }
}