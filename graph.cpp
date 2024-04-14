#include <iostream>
#include <iomanip>
#include "graph.h"
#include "heap.h"
#include "stack.h"
using namespace std;

int sourceVertex = 0;
int destination = 0;
bool ifsinglesource = false;

void initSingleSource(pVERTEX* V, int numVer, int source) {
    // Initialize single source for Dijkstra's algorithm
    for (int i = 0; i < numVer; i++) {
        V[i]->key = INFINITY; // Set initial key values to infinity
        V[i]->previous = -1; // Set initial predecessor to NIL
        // printf("index: %d\n",V[i]->index);
        // printf("Distance: %lf\n\n",V[i]->distance);
    }
    V[source-1]->key = 0; // Set key of source vertex to 0
}

// u and v are pointers to the vertex and w is the weight of the edge between them.
bool relax(pVERTEX u, pVERTEX v, double w) {
    bool ifchanged = false;
    if (v->key > u->key + w) {
        ifchanged = true;
        v->key = u->key + w; // Update vertex v's distance
        v->previous = u->id; // Set vertex v's predecessor to the index of vertex u
    }
    return ifchanged;
}



void dijkistra(pVERTEX* V, int numver, int sourceVer, pNODE* adjList){
    sourceVertex = sourceVer;
    ifsinglesource = true;

    HEAP* heap = new HEAP; // priority queue - min heap
    heap->capacity = numver;
    heap->size = 0;
    heap->A = new VERTEX*[heap->capacity];
    for(int i=0;i<heap->capacity;i++){
        heap->A[i] = new VERTEX;
    }
    STACK* stack = new STACK; //new stack
    stack->size = numver;
    stack->S = new STACK_NODE*[numver];
    for(int i = 0; i < numver; i++) {
        stack->S[i] = new STACK_NODE; // Allocate memory for each stack node
        stack->S[i]->ver = new VERTEX; // Allocate memory for the vertex
    }
    if(heap == NULL){
        printf("Error: Failed to allocate memory for HEAP.\n");
        return;
    }

    for(int i=0;i<numver;i++){
        insertion(heap,V[i]);
    }
    printHeap(heap);
    printf("here");
    while(heap->size!=0){
        pVERTEX newV = extractMin(heap);
        push(stack,newV);
        printf("index of extract min vertex %d.\n",newV->id);
        pNODE edge = adjList[newV->id-1]; 
        int nodecount = 1;
        while(edge->next!=NULL){
            edge = edge->next;
            nodecount++;
        }
        pNODE Edge = adjList[newV->id-1];
        for(int j= 0;j<nodecount;j++){
            if(relax(newV,V[Edge->v-1],Edge->w)){
                decreaseKey(heap,V[Edge->v-1]->heappos,newV->key + Edge->w);
            }
            Edge = Edge->next;
        }
        heapify(heap,0);
        printHeap(heap);
    }
}

void initSinglePair(pVERTEX* V, int n, int source, int destination) {
    for (int i = 1; i <= n; i++) {
        if (i == source) {
            V[i]->key = 0; // Set key of source vertex to 0
        } else {
            V[i]->key = INFINITY; // Set initial key values to infinity
        }
        V[i]->previous = -1; // Set initial predecessor to NIL
    }
}

void printlength(int s, int t){
    if(ifsinglesource){
        if(sourceVertex != s){
            return ;
        }
    }else{
        if(sourceVertex != s && destination != t){
            return;
        }
    }



}

void printPath(int s, int t){

}