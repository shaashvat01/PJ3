// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: data_structures.h contains all the data structures defined for this code. All the Vertex, edge,
// heap and stack data structures are defined here.

#ifndef _data_structures_h
#define _data_structures_h 1

// data structure for the vertex
typedef struct TAG_VERTEX
{
    int id;  // index
    double key;  // disatnce
    int pos;  // position of the vertex in the min-heap array
    int prev;  // previous
    int h_pos;  // position in the heap
}VERTEX;
typedef VERTEX *pVertex;  // pointer for the vertex

// data structure for the node/edge
typedef struct TAG_EDGE
{
    int id; // index
    int start; 
    int end;
    double weight; 
    TAG_EDGE *next;  // pointer to the next 
}EDGE;
typedef EDGE *pEDGE;  // pointer for edge

// for heap implementation
typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;

// data structure for the heap
typedef struct TAG_HEAP
{
    int capacity;  // maximum capicity of the heap
    int size;  // size
    pELEMENT *A;  // A heap 
}HEAP;

// data structure for the stack
typedef struct TAG_STACK_EDGE
{
    VERTEX* vertex;  // vertex pointer
    TAG_STACK_EDGE* next;  //next pointer
} STACK_EDGE;

// data structure for the stack
typedef struct TAG_STACK
{
    STACK_EDGE** Stack; // stack array
    STACK_EDGE* head;  // top of stack
    int size;  // size of stack
} STACK;

#endif