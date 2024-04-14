#include <iostream>
#include <iomanip>
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
using namespace std;

int sourceVer;

void initSingleSource(pVertex* V, int vertices, int source) {
    // Initialize single source for Dijkstra's algorithm
    for (int i = 0; i < vertices; ++i) {
        V[i]->key = INFINITY; // Set initial key values to infinity
        V[i]->pi = -1; // Set initial predecessor to NIL
    }
    V[source]->key = 0; // Set key of source vertex to 0
}

bool relax(pVertex u, pVertex v, double w) {
    double newKey = u->key + w;
    if (v->key > newKey) {
        cout << "Relaxing vertex " << v->id << " from key " << v->key << " to new key " << newKey << endl;
        v->key = newKey;  // Make sure the key is updated here
        v->pi = u->id;
        return true;
    }
    return false;
}

void singleSource(pVertex* V, int vertices, int source, pEdge* adjList)
{
    // sourceVer = source;
    // ifsinglesource = true;
    initSingleSource(V, vertices, source);

    pHEAP heap = init(vertices); // priority queue - min heap
    STACK *stack = init();

    if(heap == NULL || stack == NULL)
    {
        cout << "Error." << endl;
        return;
    }

    for(int i = 0; i<vertices; i++)
    {
        insertH(heap, V[i]);
        //V[i]->position = i;  // new
        printf("%d\n",V[i]->id);
        printf("%lf\n",V[i]->key);
    }

    for(int i = 0; i < vertices; i++)
    {
        heap->A[i]->position = i;
    }

    while(heap->size != 0)
    {
        VERTEX* u = extractMin(heap);
        push(stack,u);

        for (pEdge edg = adjList[u->id]; edg != NULL; edg = edg->next) 
        {
            pVertex v = V[edg->v];
            if (relax(u, v, edg->w)) 
            {
                if(v->key < u->key + edg->w)
                {
                    decreaseKey(heap, v->position, v->key);
                }
            }
        }
    }

    VERTEX* pVertex;
    for(int i = 0; i < vertices; i ++)
    {
        pVertex = pop(stack); 
        printf("%d\n",pVertex->id);
    }
}


// void initSinglePair(pVertex* V, int n, int source, int destination) {
//     for (int i = 1; i <= n; i++) {
//         if (i == source) {
//             V[i]->key = 0; // Set key of source vertex to 0
//         } else {
//             V[i]->key = INFINITY; // Set initial key values to infinity
//         }
//         V[i]->pi = -1; // Set initial predecessor to NIL
//     }
// }