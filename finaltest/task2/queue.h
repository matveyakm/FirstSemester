#pragma once
#include <stdbool.h>
#define OK 0
#define NULL_POINTER 1
#define QUEUE_IS_EMPTY 2


typedef struct Queue Queue;

Queue *createQueue();
bool isQueueEmpty(Queue *queue, int *errorCode);
void enqueue(Queue *queue, int value, int *errorCode);
int peekQueue(Queue *queue, int *errorCode);
int dequeue(Queue *queue, int *errorCode);
void freeQueue(Queue *queue, int *errorCode);