#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool isArraySorted(int *arrayNeedToCheck, const int arrayLength) {
    if (arrayLength <= 1) {
        return true;
    }
    for (int i = 1; i < arrayLength; i++) {
        if (arrayNeedToCheck[i-1] > arrayNeedToCheck[i]) {
            return false;
        }
    }
    return true;
}

void reverse(int *arrayNeedToReverse, int arrayLength) {
    for (int i = 0; i < arrayLength / 2; ++i) {
        swap(&arrayNeedToReverse[i], &arrayNeedToReverse[arrayLength - i - 1]);
    }
}

bool areArraysEqual(int *firstArray, int *secondArray, int arraysLength) {
    for (int i = 0; i < arraysLength; ++i) {
        if (firstArray[i] != secondArray[i]) {
            return false;
        }
    }
    return true;
}