// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: stack.cpp contains the major functionality for the stack. It contains important functions like
// push and pop which are being used to add and remove the value from the stack.

#include "stack.h"
#include "data_structures.h"
#include "math.h"
#include <iostream>
using namespace std;

// pushing/adding value to the stack.
void push(STACK* Stack, VERTEX* vertex)
{
    // Incrementing the size of the stack.
    Stack->size++;
    // creating a new stack edge node object.
    STACK_EDGE* node = (STACK_EDGE*)malloc(sizeof(STACK_EDGE));
    node->vertex = vertex;
    node->next = NULL;

    // if stack is NULL then new node becomes the head of the stack.
    if(Stack->head == NULL)
    {
        Stack->head = node; // initializing the new node as the satck head.
    }
    // if not then new node is added at the beginning of the stack.
    else
    {
        node->next = Stack->head; // next value is head
        Stack->head = node; // head is node.
    }
}

// popping/removing the values from the stack.
VERTEX* pop(STACK* Stack)
{
    // if stack is NULL then return.
    if(Stack->head == NULL)
    {
        return NULL;
    }

    STACK_EDGE* edge = Stack->head; // storing the top edge of the stack
    VERTEX* vertex = Stack->head->vertex;  // storing the ertex from the top edge of the stack.

    Stack->head = Stack->head->next;  // head = next node
    
    delete edge;  // free the memory of the top edge.
    Stack->size--;  // decrementing the size of the stack.

    return vertex;  // returning the popoed value.
}