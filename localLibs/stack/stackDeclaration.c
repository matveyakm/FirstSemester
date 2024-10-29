#include <stdlib.h>
#include <stdbool.h>
#include "stackDeclaration.h"

typedef struct StackElement {
    int value;
    struct StackElement *next;
} StackElement;

struct Stack {
    StackElement *head;
};

void *createElement(int value) {
    StackElement *newElement = malloc(sizeof(StackElement));
    newElement->value = value;
    newElement->next = NULL;
    return newElement;
}

Stack *createStack() {
    Stack *stack = calloc(sizeof(StackElement), sizeof(Stack));
    return stack;
}

bool isEmpty(Stack *stack) {
    return stack->head == NULL;
}

int peek(Stack *stack) {
    return stack->head->value;
}

void push(Stack *stack, int value) {
    StackElement *newElement = createElement(value);
    newElement->next = stack->head;
    stack->head = newElement;
}

void pop(Stack *stack) {
    StackElement *temp = stack->head;
    stack->head = (stack->head)->next;
    free(temp);
}

void deleteStack(Stack *stack) {
    while (!isEmpty(stack->head)) {
        pop(stack->head);
    }
    free(stack);
}