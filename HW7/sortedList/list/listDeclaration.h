#pragma once
#include <stdbool.h>

typedef struct SortedList SortedList;

SortedList *createSortedList(int capacity);
int getSortedListLength(SortedList *list);
void resizeList(SortedList *list);
void addValue(SortedList *list, int value);
bool deleteValue(SortedList *list, int value);
int *copySortedListIntoArray(SortedList *list, int *size);
SortedList *copyArrayIntoSortedList(int *array, int size);
void deleteSortedList(SortedList *list);
void printSortedList(SortedList *list);