#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../binSearch/binSearch.h"

void initializeSeed(int seed) {
    if (seed == 0) {
        srand(clock()); 
    } else {
        srand(seed);
    }
}

void fillRandomArray(int *array, int arrayLength, int low, int high) {
    int rangeСoefficient = high - low + 1;
    for (int i = 0; i < arrayLength; i++) {
        array[i] = rand() % rangeСoefficient + low;
    }
}

void fillRandomSet(int *array, int arrayLength, int low, int high) {
    int rangeСoefficient = high - low + 1;
    for (int i = 0; i < arrayLength; ++i) {
        int element = rand() % rangeСoefficient + low;
        while (isIn(element, array, arrayLength)) {
            element = rand() % rangeСoefficient + low;
        }
        array[i] = element;
    }
}

void randomizeArray(int *array, int arrayLength, int seed) {
    initializeSeed(seed);
    fillRandomArray(array, arrayLength, -1000, 1000);
}

void randomizeSet(int *array, int arrayLength, int seed) {
    initializeSeed(seed);
    fillRandomSet(array, arrayLength, -1000, 1000);
}

void randomizeArrayInRange(int *array, int arrayLength, int seed, int low, int high) {
    initializeSeed(seed);
    fillRandomArray(array, arrayLength, low, high);
}

void randomizeSetInRange(int *array, int arrayLength, int seed, int low, int high) {
    initializeSeed(seed);
    fillRandomSet(array, arrayLength, low, high);
}

void printArray(int *array, int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    puts("");
}

double convertTime(const clock_t time) { // ms
  return (double)time / (CLOCKS_PER_SEC / 1000.0);
}