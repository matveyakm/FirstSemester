#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queueDeclaration.h"

typedef struct Element {
    int value;
    struct Element *next;
} Element;

struct Queue {
    Element *front;
    Element *rear;
};

void *createElement(int value) {
    Element *newElement = malloc(sizeof(Element));
    newElement->value = value;
    newElement->next = NULL; //
    return newElement;
}

Queue *createQueue() {
    Queue *queue = calloc(sizeof(Element), sizeof(Queue));
    return queue;
}

bool isEmpty(Queue *queue) {
    return queue->front == NULL;
}

void enqueue(Queue *queue, int value) {
    Element *newElement = createElement(value);

    if (isEmpty(queue)) {
        queue->front = newElement;
    } else {
        queue->rear->next = newElement;
    }
    queue->rear = newElement;
}

int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
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

int peek(Queue *queue) {
    if (isEmpty(queue)) {
        return 1;
    }
    return queue->front->value;
}

void deleteQueue(Queue *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue); //
}