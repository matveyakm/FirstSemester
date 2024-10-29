#include <stdio.h>
#include <stdlib.h>
#include "../../localLibs/arrayFuncs/arrayFuncs.h"

void customizedInsertionSort(int *arrayNeedToSort, const int begin, const int arrayLength) {
    if (arrayLength <= 1) return;
    for (int i = 1 + begin; i < begin + arrayLength; i++) {
        int currentElement = arrayNeedToSort[i];
        int j = i - 1; // filling index
        while (j >= 0 && arrayNeedToSort[j] > currentElement) {
            arrayNeedToSort[j + 1] = arrayNeedToSort[j];
            --j;
        }
        arrayNeedToSort[j + 1] = currentElement;
    }
}

int smartQSortPartition(int *array, const int low, const int high) { 
    const int pivot = array[high]; // can be more variable
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            ++i;  
            swap(&array[i], &array[j]); 
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void subSmartQSort(int *arrayNeedToSort, const int low, const int high) {
    if (high - low <= 10) {
        customizedInsertionSort(arrayNeedToSort, low, high - low + 1);
    } else if (low < high) {
        const int midElementIndex = smartQSortPartition(arrayNeedToSort, low, high);

        subSmartQSort(arrayNeedToSort, low, midElementIndex - 1);
        subSmartQSort(arrayNeedToSort, midElementIndex + 1, high);
    }
}   

void smartQSorting(int *arrayNeedToSort, const int arrayLength) {
    if (arrayLength <= 1 || arrayNeedToSort == NULL) {
        return;
    }
    subSmartQSort(arrayNeedToSort, 0, arrayLength - 1);
}