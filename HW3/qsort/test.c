#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../../localLibs/arrayFuncs/arrayFuncs.h"
#include "../../localLibs/testingTools/testingTools.h"
#include "../../localLibs/qsort/qsort.h"
#include "smartQSort.h"

typedef struct {
  double qsort;
  double smartQSort;
} TimeUsed;

bool defaultTest() { // compare with prefilled
    int defaultArray[] = {52, 144, 0, -2, 6, 3, 7, 3, 99};
    int defaultArrayLength = sizeof(defaultArray) / sizeof(defaultArray[0]);

    smartQSorting(defaultArray, defaultArrayLength);

    int expectingResult[] = {-2, 0, 3, 3, 6, 7, 52, 99, 144};
    
    return areArraysEqual(defaultArray, expectingResult, defaultArrayLength);
}

bool validationTest(bool needToDisplayTimeUsedByMethods) {
    bool isTestSuccesful = defaultTest();
    int seed[] = {52, 666, 4, 89, 5843, 101, 123, 5, 54358, 33, 947};
    int countOfSeeds = sizeof(seed) / sizeof(seed[0]);

    const int arrayLength = 100000;
    int *arrayNeedToTestClassicWay = malloc(arrayLength * sizeof(int));
    int *arrayNeedToTestSmartWay = malloc(arrayLength * sizeof(int));

    TimeUsed timeUsed = {0, 0};
    clock_t beginOfSorting;

    for (int seedPeaker = 0; seedPeaker < countOfSeeds; ++seedPeaker) {
        randomizeArrayInRange(arrayNeedToTestClassicWay, arrayLength, seed[seedPeaker], -100000, 100000);
        randomizeArrayInRange(arrayNeedToTestSmartWay, arrayLength, seed[seedPeaker], -100000, 100000);

        beginOfSorting = clock();
        qsorting(arrayNeedToTestClassicWay, arrayLength);
        timeUsed.qsort += convertTime(clock() - beginOfSorting);

        beginOfSorting = clock();
        smartQSorting(arrayNeedToTestSmartWay, arrayLength);
        timeUsed.smartQSort += convertTime(clock() - beginOfSorting);

        isTestSuccesful *= isArraySorted(arrayNeedToTestClassicWay, arrayLength);
        isTestSuccesful *= isArraySorted(arrayNeedToTestSmartWay, arrayLength);
        isTestSuccesful *= areArraysEqual(arrayNeedToTestClassicWay, arrayNeedToTestSmartWay, arrayLength);
    }

    free(arrayNeedToTestClassicWay);
    free(arrayNeedToTestSmartWay);

    puts(isTestSuccesful ? "Test succesful\n" : "Test failed\n");
    if (needToDisplayTimeUsedByMethods) {
        printf("Classic quick sort used %.5f ms (%d elements)\n", timeUsed.qsort / countOfSeeds, arrayLength);
        printf("Smart quick sort used %.5f ms (%d elements)\n", timeUsed.smartQSort / countOfSeeds, arrayLength);
    }

    return isTestSuccesful;
}