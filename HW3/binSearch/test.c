#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../../localLibs/qsort/qsort.h"
#include "../../localLibs/binSearch/binSearch.h"
#include "../../localLibs/testingTools/testingTools.h"

typedef struct {
  double findingEachOneInNotSorted;
  double findingEachOneWithSorting;
  double findingEachOneInSorted;
  double findForFullArray;
} TimeUsed;

const bool defaultTest() { // comparing with prefilled
    int array[] = {6, 52, 4234, 576, 0, -3454, 43, 898};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    int targets[] = {777, 0, 43, 52, 58493, 9, -999, 4234, 898, 943};
    int targetsLength = sizeof(targets) / sizeof(targets[0]);
    int answers[] = {-1, 4, 6, 1, -1, -1, -1, 2, 7, -1};
    for (int t = 0; t < targetsLength; t++) {
            int result = find(targets[t], array, arrayLength);
            if (result != answers[t]) {
                return false;
            }
    }
    return true;
}

const bool validationTest() {
    bool isTestSuccesful = defaultTest();
    TimeUsed timeUsed = {0.0f, 0.0f, 0.0f, 0.0f};
    clock_t begin;

    int seed[] = {52, 666, 3, 415, 78, 999, 965, 64}; 
    int seedLength = sizeof(seed) / sizeof(seed[0]);
    int arrayLength = 10240;
    int *array = malloc(arrayLength * sizeof(int));
    int *arrayCopy = malloc(arrayLength * sizeof(int));

    for (int i = 0; i < seedLength; i++) {
        randomizeSetInRange(array, arrayLength, seed[i], -100000, 100000);
        
        for (int j = 0; j < arrayLength; j++) {
            begin = clock();
            isTestSuccesful *= find(array[j], array, arrayLength) == j; // n * n
            timeUsed.findingEachOneInNotSorted += convertTime(clock() - begin);
        }

        begin = clock();
        qsorting(array, arrayLength);
        timeUsed.findingEachOneWithSorting += convertTime(clock() - begin);
        begin = clock();
        for (int j = 0; j < arrayLength; j++) {
            isTestSuccesful *= find(array[j], array, arrayLength) == j; // n * logn
        }
        timeUsed.findingEachOneInSorted += convertTime(clock() - begin);

        memcpy(arrayCopy, array, arrayLength * sizeof(int));
        begin = clock();
        findFromArray(arrayCopy, array, arrayLength, arrayLength); // faster than n * logn
        timeUsed.findForFullArray += convertTime(clock() - begin) + timeUsed.findingEachOneWithSorting;
        for (int j = 0; j < arrayLength; j++) {
            isTestSuccesful *= arrayCopy[j] == j;
        }
        timeUsed.findingEachOneWithSorting += timeUsed.findingEachOneInSorted;

    }

    free(array);
    free(arrayCopy);

    puts(isTestSuccesful ? "Test succesful\n" : "Test failed\n");
    printf("findingEachOneInNotSorted used %.5fms\n", timeUsed.findingEachOneInNotSorted);
    printf("findingEachOneInSorted used %.5fms\n", timeUsed.findingEachOneInSorted);
    printf("findingEachOneWithSorting used %.5fms\n", timeUsed.findingEachOneWithSorting);
    printf("findingForFullArray used %.5fms\n", timeUsed.findForFullArray);

    return isTestSuccesful;
}