#include <iostream>
#include <iomanip>
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "util.h"
#include "math.h"
using namespace std;

int num1 = 0;
//int destination = 0;
bool check1 = false;
int recent_source = 0;
int recent_destination = 0;
pVertex* vertex_list;
STACK* g_stack = (STACK*)malloc(sizeof(STACK));

void initSingleSource(pVertex* V, int vertices, int source) {
    // Initialize single source for Dijkstra's algorithm
    for (int i = 0; i < vertices; i++) {
        V[i]->key = INFINITY; // Set initial key values to infinity
        V[i]->prev = -1; // Set initial predecessor to NIL
    }
    V[source-1]->key = 0; // Set key of source vertex to 0
}

// u and v are pointers to the vertex and w is the weight of the edge between them.
bool relax(pVertex start, pVertex end, double weight) {
    bool check = false;
    if (end->key > start->key + weight) {
        check = true;
        end->key = start->key + weight; // Update vertex v's distance
        end->prev = start->id; // Set vertex v's predecessor to the index of vertex u
    }
    return check;
}

void singleSource(pVertex* V, int vertices, int vSource, pEDGE* adjList, int destination){
    recent_source = vSource;
    recent_destination = destination;
    num1 = vSource;
    check1 = true;
    
    //HEAP* heap = new HEAP; // priority queue - min heap
    HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
    heap->capacity = vertices;
    heap->size = 0;
    heap->A = new VERTEX*[heap->capacity];

    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->size = 0;
    stack->Stack = new STACK_EDGE*[vertices];
    g_stack = stack;

    if(heap == NULL){
        fprintf(stdout,"Error: Failed to allocate memory for HEAP.");
        return;
    }

    for(int i=0;i<vertices;i++){
        insertH(heap,V[i]);
    }
    
    while(heap->size!=0){
        pVertex newV = extractMin(heap);
        pEDGE edge = adjList[newV->id-1]; 
        int nodecount = 1;

        while(edge->next!=NULL){
            edge = edge->next;
            nodecount++;
        }
        pEDGE Edge = adjList[newV->id-1];
        bool decrease;
        for(int j= 0;j<nodecount;j++){
            decrease = relax(newV,V[Edge->end-1],Edge->weight);
            if(decrease)
            {
                decreaseKey(heap,V[Edge->end-1]->h_pos,newV->key + Edge->weight);
            }
            Edge = Edge->next;
        }
        heapify(heap,0);
        if(destination == newV->id)
        {
            break;
        }
    }
    vertex_list = V;
}

void initSinglePair(pVertex* V, int n, int source, int destination) {
    for (int i = 1; i <= n; i++) {
        if (i == source) {
            V[i-1]->key = 0; // Set key of source vertex to 0
        } else {
            V[i-1]->key = INFINITY; // Set initial key values to infinity
        }
        V[i-1]->prev = -1; // Set initial predecessor to NIL
    }
}

void printlength(int s, int t)
{
    if(recent_source != s)
    {
        return; // wring source vertex
    }
    if(recent_destination!= t &&recent_destination!=0 )
    {
        return; // wring destination vertex
    }
    if(recent_destination==0)
    {
        if(vertex_list[t-1]->key == INFINITY)
        {
            fprintf(stdout,"There is no path from %d to %d.\n",s,t);
        }
        else
        {
            fprintf(stdout,"The length of the shortest path from %d to %d is:     %.2lf\n",s,t,vertex_list[t-1]->key);
        }
    }
    else 
    {
        fprintf(stdout,"The length of the shortest path from %d to %d is:     %.2lf\n",s,t,vertex_list[t-1]->key);
    }
}

void printPath(int source,int target)
{
    //empty the stack
    while (g_stack->size != 0)
    {
        pop(g_stack);
    }

    //populate g_stack with vertex in order of pi
    int ctr = target;
    if(vertex_list[ctr-1]->prev > 0)
    {
        push(g_stack,vertex_list[ctr-1]);
        ctr = vertex_list[ctr-1]->prev;
        while(ctr > 0)
        {
            push(g_stack,vertex_list[ctr-1]);
            ctr = vertex_list[ctr-1]->prev;
        }
    }
    else
    {
        fprintf(stdout,"There is no path from %d to %d.\n",source,target);
        return;
    }

    if(g_stack->size != 0 )
    {
        fprintf(stdout,"The shortest path from %d to %d is:\n",source,target);
    }
    
    while (g_stack->size != 0)
    {
        VERTEX* temp = pop(g_stack);
        fprintf(stdout,"[%d:%8.2f]",temp->id,temp->key);
        if(g_stack->size == 0)
        {
            fprintf(stdout,".\n");
        }
        else
        {
            fprintf(stdout,"-->");
        }
    } 
}