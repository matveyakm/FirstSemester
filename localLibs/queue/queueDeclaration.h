#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Queue Queue;

Queue *createQueue();
bool isQueueEmpty(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
int peekQueue(Queue *queue);
void clearQueue(Queue *queue);
