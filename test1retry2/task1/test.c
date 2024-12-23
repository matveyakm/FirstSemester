#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maxSumOfDigits.h"

static bool testThatShouldReturnOneElement(void) {
    int array[] = {41, 1000, 94, 32, 9, 3, 1};
    int arrayLength = sizeof(array) / sizeof(array[0]);

    int lengthOfArrayWithNumbersWithMaxSum = -1;
    int *numbersWithMaxSum = findNumberWithMaxSumOfDigits(array, arrayLength, &lengthOfArrayWithNumbersWithMaxSum);
    if (!numbersWithMaxSum) {
        return false;
    }
    bool isTestSuccessful = numbersWithMaxSum[0] == 94 && lengthOfArrayWithNumbersWithMaxSum == 1;
    free(numbersWithMaxSum);
    return isTestSuccessful;
}

static bool testWithNormalData(void) {
    int array[] = {9, -45, 6, 10000, 54, 3, 13, 14};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    
    int lengthOfArrayWithNumbersWithMaxSum = -1;
    int *numbersWithMaxSum = findNumberWithMaxSumOfDigits(array, arrayLength, &lengthOfArrayWithNumbersWithMaxSum);
    if (!numbersWithMaxSum) {
        return false;
    }
    int correctResult[] = {9, -45, 54};
    for (int i = 0; i < 3; ++i) {
        if (numbersWithMaxSum[i] != correctResult[i]) {
            free(numbersWithMaxSum);
            return false;
        }
    }
    free(numbersWithMaxSum);
    return lengthOfArrayWithNumbersWithMaxSum == 3;
}

static bool testWithSpecialCases(void) {
    int oneElementArray[] = {52};
    int lengthOfArrayWithNumbersWithMaxSum = -1;
    bool isTestSuccessful = true;
    isTestSuccessful *= findNumberWithMaxSumOfDigits(NULL, 4, &lengthOfArrayWithNumbersWithMaxSum) == NULL;
    int *oneElementResult = findNumberWithMaxSumOfDigits(oneElementArray, 1, &lengthOfArrayWithNumbersWithMaxSum);
    isTestSuccessful *= oneElementResult[0] == 52 && lengthOfArrayWithNumbersWithMaxSum == 1;
    free(oneElementResult);
    return isTestSuccessful;
}

bool validationTest(void) {
    return testThatShouldReturnOneElement() && testWithNormalData() && testWithSpecialCases();
}