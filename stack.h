#ifndef stack_h
#define stack_h 1
#include "data_structures.h"

STACK* init();
void push(STACK* stack, pVertex vertex);
VERTEX* pop(STACK* stack);
bool empty(STACK* stack);

#endif