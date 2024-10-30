#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Stack Stack;

Stack *createStack();
bool isEmpty(Stack *stack);
int peek(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void deleteStack(Stack *stack);