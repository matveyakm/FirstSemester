#pragma once
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define NULL_POINTER_PASSED 521
#define ALLOCATION_ERROR 110
#define OUT_OF_LENGTH 520

typedef struct List List;

List *createList(int length);
int getListLength(List *list);
void addL(List *list, int position, int value, int *errorCode);
int popAtL(List *list, int position, int *errorCode);
int peekL(List *list, int position, int *errorCode);
void appendL(List *list, int value, int *errorCode);
int popL(List *list, int *errorCode);
void printList(List *list);
int *copyListIntoArray(List *list);
List *copyArrayIntoList(int *array, int arrayLength);
void deleteList(List *list);