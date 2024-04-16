#include <iostream>
#include <iomanip>
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "util.h"
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

    HEAP* heap = new HEAP; // priority queue - min heap
    heap->capacity = vertices;
    heap->size = 0;
    heap->A = new VERTEX*[heap->capacity];
    // for(int i=0;i<heap->capacity;i++){
    //     heap->A[i] = new VERTEX;
    // }
    STACK* stack = new STACK; //new stack
    stack->size = 0;
    stack->Stack = new STACK_EDGE*[vertices];
    g_stack = stack;
    // for(int i = 0; i < vertices; i++) {
    //     stack->Stack[i] = new STACK_EDGE; // Allocate memory for each stack node
    //     stack->Stack[i]->vertex = new VERTEX; // Allocate memory for the vertex
    // }
    if(heap == NULL){
        printf("Error: Failed to allocate memory for HEAP.\n");
        return;
    }

    for(int i=0;i<vertices;i++){
        insertH(heap,V[i]);
    }
    printH(heap);
    
    while(heap->size!=0){
        pVertex newV = extractMin(heap);
        push(stack,newV);
        if(destination == newV->id)
        {
            break;
        }
        //printf("index of extract min vertex %d.\n",newV->id);
        pEDGE edge = adjList[newV->id-1]; 
        int nodecount = 1;
        while(edge->next!=NULL){
            edge = edge->next;
            nodecount++;
        }
        pEDGE Edge = adjList[newV->id-1];
        for(int j= 0;j<nodecount;j++){
            if(relax(newV,V[Edge->end-1],Edge->weight)){
                decreaseKey(heap,V[Edge->end-1]->h_pos,newV->key + Edge->weight);
            }
            Edge = Edge->next;
        }
        heapify(heap,0);
        printH(heap);
    }
    vertex_list = V;

    // STACK_EDGE* newStackNode = stack->head;
    // fprintf(stdout,"%d", stack->size);
    // for(int i=0;i<stack->size-1;i++){
    //     pVertex newVV = newStackNode->vertex;
    //     fprintf(stdout,"Element %d in stack, %d\n",i,newVV->id);
    //     newStackNode = newStackNode->next;
    // }
    //fprintf(stdout,"%d", stack->size);
}

void initSinglePair(pVertex* V, int n, int source, int destination) {
    for (int i = 0; i < n; i++) {
        if (i == source) {
            V[i]->key = 0; // Set key of source vertex to 0
        } else {
            V[i]->key = INFINITY; // Set initial key values to infinity
        }
        V[i]->prev = -1; // Set initial predecessor to NIL
    }
}

void printlength(int s, int t)
{
    if(recent_source != s)
    {
        fprintf(stdout,"This is wrong source vertex");
        return;
    }
    if(recent_destination!= t &&recent_destination!=0 )
    {
        fprintf(stdout,"This is wrong destination vertex");
        return;
    }
    if(recent_destination==0)
    {
        if(vertex_list[t-1]->key == INFINITY)
        {
            printf("There is no path from %d to %d.\n",s,t);
        }
        else
        {
            fprintf(stdout,"The length of the shortest path from %d to %d is: %lf\n",s,t,vertex_list[t-1]->key);
        }
    }
    else 
    {
        fprintf(stdout,"The length of the shortest path from %d to %d is: %lf\n",s,t,vertex_list[t-1]->key);
    }
}

void printPath(int s, int t){

    STACK_EDGE* e_stack = g_stack->head;

    if(recent_source != s){
        fprintf(stdout,"This is wrong source vertex");
        return;
    }
    if(recent_destination!= t &&recent_destination!=0 ){
        fprintf(stdout,"This is wrong destination vertex");
        return;
    }
    if(recent_destination==0)
    {
        if(vertex_list[t-1]->key == INFINITY)
        {
            printf("There is no path from %d to %d.\n",s,t);
        }
        else
        {
            fprintf(stdout,"[%d: %lf]",e_stack->vertex->id,e_stack->vertex->key);
            e_stack = e_stack->next;
            while(e_stack != NULL)
            {
                fprintf(stdout,"-->[%d: %lf]",e_stack->vertex->id,e_stack->vertex->key);
                if(e_stack->vertex->id == t)
                {
                    return;
                }
                e_stack = e_stack->next;
            }
        }
    }
    else
    {
        fprintf(stdout,"[%d: %lf]",e_stack->vertex->id,e_stack->vertex->key);
        e_stack = e_stack->next;
        while(e_stack != NULL)
        {
            fprintf(stdout,"-->[%d: %lf]",e_stack->vertex->id,e_stack->vertex->key);
            if(e_stack->vertex->id == t)
            {
                return;
            }
            e_stack = e_stack->next;
        }
    }
}