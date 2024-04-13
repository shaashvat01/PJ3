#include <iostream>
#include <iomanip>
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
using namespace std;

void initSingleSource(pVertex* V, int vertices, int source) {
    // Initialize single source for Dijkstra's algorithm
    for (int i = 0; i < vertices; ++i) {
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
    initSingleSource(V, vertices, source);

    pHEAP heap = init(vertices); // priority queue - min heap
    STACK *stack = init();

    // if(heap == NULL)
    // {
    //     cout << "Priority Queue not initialized." << endl;
    //     return;
    // }

    // if(stack == NULL)
    // {
    //     cout << "stack not initialized." << endl;
    //     return;
    // }

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

        for(pEdge edg = adjList[u->id]; edg != NULL; edg = edg->next)
        {
            pVertex v = V[edg->v];
            if(v->key > u->key + edg->w)
            {
                relax(u,v,edg->w);
                //cout << "Able to relax" <<endl;
                decreaseKey(heap, v->position, v->key);
            }
            //cout << "inside for loop" << endl;
        }
        //cout << "after push for loop\n" << endl;
    }
    //cout << "single source in graph in while after while" << endl;

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