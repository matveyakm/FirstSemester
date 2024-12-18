#include "../../localLibs/stack/stackDeclaration.h"
#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

struct Queue {
    Stack *pushingStack;
    Stack *peekingStack;
};

Queue *createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->peekingStack = createStack();
    queue->pushingStack = createStack();
    return queue;
}

bool isQueueEmpty(Queue *queue, int *errorCode) {
    *errorCode = OK;
    if (!queue) {
        *errorCode = NULL_POINTER;
        return true;
    }
    return isStackEmpty(queue->peekingStack) && isStackEmpty(queue->pushingStack);
}

void enqueue(Queue *queue, int value, int *errorCode) {
    *errorCode = OK;
    if (!queue) {
        *errorCode = NULL_POINTER;
        return;
    }
    push(queue->pushingStack, value);
}

void transferStackContent(Stack *src, Stack *dest) {
    while (!isStackEmpty(src)) {
        push(dest, pop(src));
    }
}

int peekQueue(Queue *queue, int *errorCode) {
    *errorCode = OK;
    if (!queue) {
        *errorCode = NULL_POINTER;
        return 0;
    }
    if (isQueueEmpty(queue, errorCode)) {
        *errorCode = QUEUE_IS_EMPTY;
        return 0;
    }

    if (isStackEmpty(queue->peekingStack)) {
        transferStackContent(queue->pushingStack, queue->peekingStack);
    }

    return peekStack(queue->peekingStack);
}

int dequeue(Queue *queue, int *errorCode) {
    *errorCode = OK;
    if (!queue) {
        *errorCode = NULL_POINTER;
        return 0;
    }
    if (isQueueEmpty(queue, errorCode)) {
        *errorCode = QUEUE_IS_EMPTY;
        return 0;
    }

    if (isStackEmpty(queue->peekingStack)) {
        transferStackContent(queue->pushingStack, queue->peekingStack);
    }
    return pop(queue->peekingStack);
}

void freeQueue(Queue *queue, int *errorCode) {
    *errorCode = OK;
    if (!queue) {
        *errorCode = NULL_POINTER;
        return;
    }
    clearStack(queue->peekingStack);
    clearStack(queue->pushingStack);
    free(queue);
}