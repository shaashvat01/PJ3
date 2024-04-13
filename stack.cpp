#include <iostream>
#include <iomanip>
#include "stack.h"
using namespace std;

// Initialize Stack
STACK* init()
{
    STACK* stack = (STACK*)malloc(sizeof(TAG_STACK));
    stack->head = NULL;
    return stack;
}

// adding a new vertex to the stack
void push(STACK* stack, VERTEX *vertex)
{
    TAG_STACK *element = (TAG_STACK*)malloc(sizeof(TAG_STACK));
    if(element == NULL)
    {
        fprintf(stderr, "Memory allocation failed");
        return;
    }
    element->vertex = vertex;
    element->next = stack->head; // The current head becomes the next of the new head
    stack->head = element; // New element is now the head
} 

// Pop a vertex from the Stack
VERTEX* pop(STACK* stack) {
    if (stack == NULL || stack->head == NULL) {
        cout << "Stack is empty." << endl;
        return NULL;
    }
    TAG_STACK* temp = stack->head;
    VERTEX* vertex = stack->head->vertex;
    stack->head = stack->head->next; // Update head to next element
    free(temp); // Free the popped element
    return vertex;
}

// Check if Stack is empty
bool empty(STACK* stack) {
    if (stack->head == NULL) {
        return true; 
    }
    else
    {
        return false;
    }
}