#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "../bubbleSort/bubbleSort.h"
#include "../qsort/qsort.h"
#include "../arrayFuncs/arrayFuncs.h"

int find(int targetNumber, int *array, int arrayLength); // binSearch with check for correctly sorted array.
int qfind(int targetNumber, int *array, int arrayLength); // binSearch ignoring checking
// turning -1 -- there no element in the array
bool isIn(int targetNumber, int *sortedarray, int arrayLength);

// Need for checking presence nums from one array in another using O(log) IF BOTH ARRAYS ARE SORTED
int findFromArray(int *targetNumbersArray, int *array, int targetArrayLength, int arratLength);
//filling targetNumbersArray by indexes of elements in array or -1 if is not present
//if arrays are not sorted it is filling targetNumbersArray by -2.


