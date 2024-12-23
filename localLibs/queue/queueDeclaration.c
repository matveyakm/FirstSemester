#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queueDeclaration.h"
#define QUEUE_INCLUDED

typedef struct Element {
    int value;
    struct Element *next;
} Element;

struct Queue {
    Element *front;
    Element *rear;
    int type;
};

static void *createElement(int value) {
    Element *newElement = malloc(sizeof(Element));
    newElement->value = value;
    newElement->next = NULL; //
    return newElement;
}

Queue *createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->type = 2;
    return queue;
}

bool isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void enqueue(Queue *queue, int value) {
    Element *newElement = createElement(value);
    if (isQueueEmpty(queue)) {
        queue->front = newElement;
    } else {
        queue->rear->next = newElement;
    }
    queue->rear = newElement;
}

int dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        return 1;
    }
    Element *temp = queue->front;
    int value = temp->value;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return value;
}

int peekQueue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        return 1;
    }
    return queue->front->value;
}

void clearQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue); 
}