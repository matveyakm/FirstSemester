#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Stack Stack;

Stack *createStack();
bool isStackEmpty(Stack *stack);
int peekStack(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void clearStack(Stack *stack);
