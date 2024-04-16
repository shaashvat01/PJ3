#include "stack.h"
#include "data_structures.h"
#include <iostream>
using namespace std;

void push(STACK* Stack, VERTEX* vertex)
{
    Stack->size++;
    STACK_EDGE* node = (STACK_EDGE*)malloc(sizeof(STACK_EDGE));
    pVertex newV = vertex;
    node->vertex = vertex;
    node->next = NULL;
    if(Stack->head == NULL)
    {
        Stack->head = node;
    }
    else
    {
        node->next = Stack->head;
        Stack->head = node;
    }
}

VERTEX* pop(STACK* Stack)
{
    if(Stack->head == NULL)
    {
        cout << "The stack is empty" << endl;
        return NULL;
    }
    STACK_EDGE* edge = Stack->head;
    VERTEX* newV = Stack->head->vertex;
    Stack->head = Stack->head->next;
    delete edge; 
    return newV;
    Stack->size--;
}
