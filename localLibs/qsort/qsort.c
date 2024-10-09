#include <stdio.h>
#include <stdlib.h>
#include "../arrayFuncs/arrayFuncs.h"

// Реализовать qsort, который для сортировки кусков массива размером меньше 10 использует сортировку вставкой. Поскольку qsort делит массив на части и сортирует каждую qsort-ом же, можно добиться заметного ускорения, если совсем уж маленькие части сортировать квадратичной сортировкой с меньшей константой. Эту идею и надо реализовать.

const int pushElementToMid(int *array, const int low, const int high) {
    const int pivot = array[high]; // Может быть разнообразнее
    int i = low - 1;
    for (int j = low; j < high; ++j) { // Литви вроде показывал что-то другое, но я не понял его идеи
        if (array[j] <= pivot) {
            ++i;  
            swap(&array[i], &array[j]); 
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void subQSort(int *arrayNeedToSort, const int low, const int high) {
    if (low < high) {
        const int midElementIndex = pushElementToMid(arrayNeedToSort, low, high);

        subQSort(arrayNeedToSort, low, midElementIndex - 1);
        subQSort(arrayNeedToSort, midElementIndex + 1, high);
    }
}   

void qsorting(int *arrayNeedToSort, const int arrayLength) {
    subQSort(arrayNeedToSort, 0, arrayLength - 1);
}