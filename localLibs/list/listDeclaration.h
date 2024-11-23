#pragma once
#include <stdio.h>
#include <stdlib.h>
#define INTLIST_INCLUDED

typedef struct List List;

List *createList(int length);
int listLength(List *list);
void addL(List *list, int position, int value);
int popAtL(List *list, int position);
int peekL(List *list, int position);
void appendL(List *list, int value);
int popL(List *list);
void printList(List *list);
int *listToArray(List *list);
List *arrayToList(int *array, int arrayLength);
void deleteList(List *list);