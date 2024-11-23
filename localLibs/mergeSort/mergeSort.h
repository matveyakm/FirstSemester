#pragma once
#include "../list/pointerList.h"

void mergeSort(PtrList *list, int (*compare)(void *, void *));

// compare Pointer to a comparison function that takes two void pointers 
//                and returns:
//                - < 0 if the first element is less than the second,
//                - 0 if they are equal,
//                - > 0 if greater.
//                Note: Users must cast void* to the appropriate type when implementing this function.

