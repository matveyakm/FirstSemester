#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *arrayNeedToSort, const int arrayLenth) {
    if (arrayLenth <= 1) return;
    for (int i = 1; i < arrayLenth; i++) {
        int currentElement = arrayNeedToSort[i];
        int j = i - 1; // Для перезаполнения
        while (j >= 0 && arrayNeedToSort[j] > currentElement) {
            arrayNeedToSort[j + 1] = arrayNeedToSort[j];
            --j;
        }
        arrayNeedToSort[j + 1] = currentElement;
    }
}