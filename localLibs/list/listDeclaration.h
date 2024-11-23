#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;

List *createList(int length);
int listLength(List *list);
void pushAt(List *list, int position, int value);
int popAt(List *list, int position);
int peekAt(List *list, int position);
void append(List *list, int value);
int popL(List *list);
void printList(List *list);
int *listToArray(List *list);
List *arrayToList(int *array, int arrayLength);
void deleteList(List *list);