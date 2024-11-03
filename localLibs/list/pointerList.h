#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct PtrList PtrList;

PtrList *createPtrList(int length);
int ptrListLength(PtrList *list);
void appendPtr(PtrList *list, void *data);
void pushPtr(PtrList *list, int position, void *data);
void popPtr(PtrList *list); // can only remove an element and free it
void *turnPopPtr(PtrList *list); // turning back a pointer at allocated memory. be careful
void popAtPtr(PtrList *list, int position); // can only remove an element and free it
void *turnPopAtPtr(PtrList *list, int position); // turning back a pointer at allocated memory. be careful
void *peekPtr(PtrList *list, int position); // do not free memory pointed by return of this method
void **ptrListToArray(PtrList *list);
PtrList *arrayToPtrList(void **array, int arrayLength);
void deletePtrList(PtrList *list);