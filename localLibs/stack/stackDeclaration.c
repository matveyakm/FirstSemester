#include <stdlib.h>
#include <stdbool.h>
#include "stackDeclaration.h"

typedef struct StackElement {
    int value;
    struct StackElement *next;
} StackElement;

struct Stack {
    StackElement *head;
    int type;
};

static void *createElement(int value) {
    StackElement *newElement = malloc(sizeof(StackElement));
    newElement->value = value;
    newElement->next = NULL;
    return newElement;
}

Stack *createStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->type = 1;
    return stack;
}

bool isStackEmpty(Stack *stack) {
    return stack->head == NULL;
}

int peekStack(Stack *stack) {
    return stack->head->value;
}

void push(Stack *stack, int value) {
    StackElement *newElement = createElement(value);
    newElement->next = stack->head;
    stack->head = newElement;
}

int pop(Stack *stack) {
    int removableElement = peekStack(stack);
    StackElement *temp = stack->head;
    stack->head = (stack->head)->next;
    free(temp);
    return removableElement;
}

void clearStack(Stack *stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}