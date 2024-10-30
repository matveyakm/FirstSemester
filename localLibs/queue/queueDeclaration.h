#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Queue Queue;

Queue *createQueue();
bool isEmpty(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
int peek(Queue *queue);
void deleteQueue(Queue *queue);

