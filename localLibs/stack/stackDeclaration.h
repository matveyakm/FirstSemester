#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Stack Stack;

Stack *createStack();
bool isStackEmpty(Stack *stack);
int peekStack(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void deleteStack(Stack *stack);

// If you use this header and want to be able to use 'peek' or 'isEmpty' functions,
// you have to include the containerUtils header