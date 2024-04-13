#ifndef _data_structures_h
#define _data_structures_h 1

enum class COLOR {
    White, // Vertex not visted
    Gray,  // in process
    Black  // visited
};

typedef struct GRAPH_VERTEX
{
    int id;
    COLOR color;
    double key;
    int pi;
    int position;
}VERTEX;
typedef VERTEX *pVertex;

typedef struct GRAPH_EDGE
{
    int id;
    int u;
    int v;
    double w;
    GRAPH_EDGE *next;
}EDGE;
typedef EDGE *pEdge;

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP
{
    int capacity;
    int size;
    pELEMENT *A;
}HEAP;
typedef HEAP *pHEAP;

typedef struct TAG_STACK
{
    pVertex vertex;
    struct TAG_STACK* next;
}TAG_STACK;

typedef struct STACK
{
    TAG_STACK* head;
}STACK;

#endif