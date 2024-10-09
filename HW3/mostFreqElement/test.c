#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../../localLibs/testingTools/testingTools.h"
#include "../../localLibs/qsort/qsort.h"
#include "findingMostFreqElement.h"

typedef struct {
  double linearMethodWithSorting;
  double linearMethodItself;
  double quadraticMethod;
} TimeUsed;

const bool defaultTest() {
    const int array[] = {5, 1, 4, 5, 43, -25, 43, 99, 2, 1, 55, 5, 43, 1, 5, 5, 1};
    const int arrayLength = sizeof(array) / sizeof(array[0]);
    int correctResult = 5;

    return (findForMostFreqElement(array, arrayLength) == correctResult) * (findForMostFreqElementByCounting(array, arrayLength) == correctResult);
}

const bool validationTest() { // based on method which is using counting
    int pattern[] = {1, 1, 4, 5, 43, -25, 43, 99, 2, 1, 55, 5, 43, 1, 5, 5, 1};
    const int patternLength = sizeof(pattern) / sizeof(pattern[0]);
    int repeats = 20;
    const int arrayLength = repeats * patternLength;
    int *array = malloc(arrayLength * sizeof(int));
    for (int i = 0; i < patternLength; ++i) { // filling array by pattern
        for (int rep = 0; rep < repeats; ++rep) {
            array[i * rep] = pattern[i];
        }
    }
    int *partOfArray = malloc(arrayLength * sizeof(int));

    bool isTestSuccesful = defaultTest();
    TimeUsed timeUsed = {0, 0, 0};
    clock_t beginOfCalculation;

    int i = 0;
    for (int lengthOfPart = 1; lengthOfPart < arrayLength; ++lengthOfPart) {
        while (i + lengthOfPart < arrayLength) {
            for (int partFillingIndex = 0; partFillingIndex < lengthOfPart; ++partFillingIndex) {
                partOfArray[partFillingIndex] = array[partFillingIndex + i];
            }
            int correctResult = findForMostFreqElementByCounting(partOfArray, lengthOfPart);

            beginOfCalculation = clock();
            isTestSuccesful *= quadraticFindForMostFreqElement(partOfArray, lengthOfPart) == correctResult;
            timeUsed.quadraticMethod += convertTime(clock() - beginOfCalculation);

            beginOfCalculation = clock();
            qsorting(partOfArray, lengthOfPart);
            timeUsed.linearMethodWithSorting += convertTime(clock() - beginOfCalculation);

            beginOfCalculation = clock();
            isTestSuccesful *= linearFindForMostFreqElement(partOfArray, lengthOfPart) == correctResult;
            timeUsed.linearMethodItself += convertTime(clock() - beginOfCalculation);
            ++i;
        }
        i = 0;
    }
    timeUsed.linearMethodWithSorting += timeUsed.linearMethodItself;

    puts(isTestSuccesful ? "\nTest succesful" : "\nTest failed");
    printf("Quadratic method used %.5fms\n", timeUsed.quadraticMethod);
    printf("Linear method (itself) used %.5fms\n", timeUsed.linearMethodItself);
    printf("Linear method (with sorting) used %.5fms\n", timeUsed.linearMethodWithSorting);

    free(array);
    free(partOfArray);
    return isTestSuccesful;
}