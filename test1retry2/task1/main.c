#include <stdio.h>
#include <stdlib.h>
#include "maxSumOfDigits.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest()) {
        puts("Test failed.");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    int array[] = {41, 1000, 94, 32, 9, 3, 1, -49, 2236};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    int lengthOfArrayWithNumbersWithMaxSum = -1;
    int *numbersWithMaxSum = findNumberWithMaxSumOfDigits(array, arrayLength, &lengthOfArrayWithNumbersWithMaxSum);
    if (!numbersWithMaxSum) {
        puts("Something went wrong.");
        return 1;
    }
    for (int i = 0; i < lengthOfArrayWithNumbersWithMaxSum; ++i) {
        printf("%d ", numbersWithMaxSum[i]);
    }
    free(numbersWithMaxSum);
}