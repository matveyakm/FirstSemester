#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "../bubbleSort/bubbleSort.h"
#include "../qsort/qsort.h"
#include "../arrayFuncs/arrayFuncs.h"

int findingMid(int a, int b) {
    return (a + b) / 2 + ((a + b) % 2 != 0); // 
}
int binSearch(const int targetNumber, int *array, int *searchFrom, int *searchTo) {
    if (*searchTo - *searchFrom <= 1) {
        return -1;
    }
    int mid = findingMid(*searchTo, *searchFrom);
    if (targetNumber == array[mid]) {
        return mid;
    }
    if (targetNumber > array[mid]) {
        *searchFrom = mid;
    } else {
        *searchTo = mid;
    }
    return binSearch(targetNumber, array, searchFrom, searchTo);
}

int loopSearch(const int targetNumber, int *array, const int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        if (array[i] == targetNumber) {
            return i;
        }
    }
    return -1;
}

int qfind(const int targetNumber, int *array, const int arrayLength) {
    int searchFrom = 0;
    int searchTo = arrayLength - 1;
    if (array[searchFrom] == targetNumber) {
        return searchFrom;
    } else if (array[searchTo] == targetNumber) {
        return searchTo;
    }
    return binSearch(targetNumber, array, &searchFrom, &searchTo);
}

int find(const int targetNumber, int *array, const int arrayLength) {
    if (arrayLength < 1) {
        return -1;
    }
    if (isArraySorted(array, arrayLength)) {
        return qfind(targetNumber, array, arrayLength);
    } else {
        return loopSearch(targetNumber, array, arrayLength);
    }
}

bool isIn(const int targetNumber, int *array, const int arrayLength) {
    return find(targetNumber, array, arrayLength) != -1;
}

int sortingIsIn(const int targetNumber, int *array, const int arrayLength) { // быстрее ли это, чем классика?
    int *arrayCopy = malloc(arrayLength * sizeof(int));
    memcpy(arrayCopy, array, arrayLength * sizeof(int));
    bubbleSort(arrayCopy, arrayLength);

    int result = qfind(targetNumber, arrayCopy, arrayLength) != -1;
    free(arrayCopy);
    return result; 
}

void findFromArray(int *targetNumbersArray, int *array, const int targetArrayLength, const int arrayLength) {
    if (!isArraySorted(targetNumbersArray, targetArrayLength) || !isArraySorted(array, arrayLength)) {
        for (int i = 0; i < targetArrayLength; ++i) {
            targetNumbersArray[i] = -2;
        }
        return;
    }
    int searchFrom = 0;
    int searchTo = arrayLength - 1;
    for (int i = 0; i < targetArrayLength; ++i) {
        searchTo = arrayLength - 1;
        if (array[searchFrom] == targetNumbersArray[i]) {
            targetNumbersArray[i] = searchFrom;
        } else if (array[searchTo] == targetNumbersArray[i]) {
            targetNumbersArray[i] = searchTo;
        } else {
            targetNumbersArray[i] = binSearch(targetNumbersArray[i], array, &searchFrom, &searchTo);
        }
    }
}
