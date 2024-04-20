// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: graph.cpp contains the major functionality for the graph. It contains all the important functionalities like
// dijkistra and printing.

#include <iostream>
#include <iomanip>
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "util.h"
#include "math.h"
using namespace std;

// required initializations
int num1 = 0;
bool check1 = false;
int recent_source = 0;
int recent_destination = 0;
pVertex* vertex_list;
STACK* g_stack = (STACK*)malloc(sizeof(STACK));

// Function to initialize single source for Disjkstra algorithm.
void initSingleSource(pVertex* V, int vertices, int source) 
{
    for (int i = 0; i < vertices; i++) 
    {
        V[i]->key = INFINITY; // initial key value is set to infinity
        V[i]->prev = -1; // initial predecessor is set to NULL
    }
    V[source-1]->key = 0; // the key value of source vertex is set to ero.
}

// Function to relax the edges of the graph.
bool relax(pVertex start, pVertex end, double weight) 
{
    bool check = false;  // initializing check to false.
    if (end->key > start->key + weight) 
    {
        check = true;
        end->key = start->key + weight; // updating the distance of vertex end vertex.
        end->prev = start->id; // the predecessor of end vertex is the set to the index of start.
    }
    return check;
}

// Function implements the Dijkistra algorithm.
void singleSource(pVertex* V, int vertices, int vSource, pEDGE* adjList, int destination)
{
    // updating the global initialied values to the current values.
    recent_source = vSource;
    recent_destination = destination;
    num1 = vSource;
    check1 = true;
    
    // initializing the heap.
    HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
    heap->capacity = vertices;
    heap->size = 0;
    heap->A = new VERTEX*[heap->capacity];

    // initializing the stack.
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->size = 0;
    stack->Stack = new STACK_EDGE*[vertices];
    g_stack = stack;

    // if heap is NULL then return error.
    if(heap == NULL)
    {
        fprintf(stdout,"Error: Failed to allocate memory for HEAP.");
        return;
    }
    // Insert the vertices into the heap initialized.
    for(int i=0;i<vertices;i++)
    {
        insertH(heap,V[i]);  // calling insert heap functiom.
    }
    
    // implementation of Dijkistra.
    while(heap->size != 0) // loop runs until the size is equal to 0
    {
        // extracting the minimum value from the heap and setting adjancy list.
        pVertex vert = extractMin(heap);
        pEDGE edge = adjList[vert->id-1]; 
        
        // if edge is null then continue.
        if(edge == NULL) // Most important condition check.
        {
            continue;
        }
        // counting the number of nodes in the graph.
        int nodecount = 1;
        while(edge->next != NULL) // runs until the next node is NULL.
        {
            edge = edge->next;
            nodecount++;
        }
        // getting the edge list for the current vertex.
        pEDGE Edge = adjList[vert->id-1];
        bool decrease;

        // iterating through each edge of the current vertex.
        for(int j = 0; j < nodecount ; j++){
            decrease = relax(vert,V[Edge->end-1],Edge->weight); // relax the edge.
            // if the edge is relaxed then decrease of value of the adjacent vertex in the heap.
            if(decrease)
            {
                decreaseKey(heap,V[Edge->end-1]->h_pos,vert->key + Edge->weight);
            }
            Edge = Edge->next;  // go to next edge.
        }
        // call heapify to maintain the property of the heap.
        heapify(heap,0);
        // if current vertex reached its destination then finish the loop.
        if(destination == vert->id)
        {
            break;
        }
    }
    // update the vertex list after successful execution.
    vertex_list = V;
}

// initialize the single pair algorithm.
void initSinglePair(pVertex* V, int n, int source, int destination) 
{
    for (int i = 1; i <= n; i++) 
    {
        // if i is equal to source then initialize it to 0.
        if (i == source) 
        {
            V[i-1]->key = 0; 
        } 
        // otherwose set it to infinity.
        else 
        {
            V[i-1]->key = INFINITY; 
        }
        // the previous vertex is set to neg 1.
        V[i-1]->prev = -1; 
    }
}

// function for printing the length of the edge.
void printlength(int s, int t)
{
    // source is notequal to the current source then return.
    if(recent_source != s)
    {
        return; 
    }
    // if destination is not eual to target AND destination os not equal to 0 then return.
    if(recent_destination != t && recent_destination != 0 )
    {
        return;
    }
    // if destination is equal to 0 then print length.
    if(recent_destination == 0)
    {
        // path is infinity = no path.
        if(vertex_list[t-1]->key == INFINITY)
        {
            fprintf(stdout,"There is no path from %d to %d.\n",s,t);
        }
        // print shortest path.
        else
        {
            fprintf(stdout,"The length of the shortest path from %d to %d is:     %.2lf\n",s,t,vertex_list[t-1]->key);
        }
    }
    // if not 0 then print shortest path from source to target.
    else 
    {
        fprintf(stdout,"The length of the shortest path from %d to %d is:     %.2lf\n",s,t,vertex_list[t-1]->key);
    }
}

// Funtion to print path.
void printPath(int source,int target)
{
    // popping from stack.
    while (g_stack->size != 0)
    {
        pop(g_stack);
    }
    // adding values to stack in the prder of the predecessor
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
    // no path - error
    else
    {
        fprintf(stdout,"There is no path from %d to %d.\n",source,target);
        return;
    }
    // if not empty print header.
    if(g_stack->size != 0 )
    {
        fprintf(stdout,"The shortest path from %d to %d is:\n",source,target);
    }
    // print shortest path.
    while (g_stack->size != 0)
    {
        // get vertex from stack and print its id.
        VERTEX* temp = pop(g_stack);
        fprintf(stdout,"[%d:%8.2f]",temp->id,temp->key);
        // if last vertex print id.
        if(g_stack->size == 0)
        {
            fprintf(stdout,".\n");
        }
        // else print arrow indicating more.
        else
        {
            fprintf(stdout,"-->");
        }
    } 
}