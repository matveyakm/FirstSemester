#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Queue Queue;

Queue *createQueue();
bool isQueueEmpty(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
int peekQueue(Queue *queue);
void deleteQueue(Queue *queue);

// If you use this header and want to be able to use 'peek' or 'isEmpty' functions,
// you have to include the containerUtils header