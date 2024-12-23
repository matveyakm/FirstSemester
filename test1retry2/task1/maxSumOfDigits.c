#include <stdlib.h>


int findSumOfDigits(int number) {
    int sum = 0;
    number = number < 0 ? -number : number;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int *findNumberWithMaxSumOfDigits(int *array, int arrayLength, int *outlength) {
    if (!array || arrayLength <= 0) {
        return NULL;
    }
    int maxSum = 0;
    int *numbersWithMaxSum = malloc(arrayLength * sizeof(int));
    *outlength = 0;
    if (!numbersWithMaxSum) {
        return NULL;
    }
    for (int i = 0; i < arrayLength; ++i) {
        int currentSum = findSumOfDigits(array[i]);
        if (currentSum > maxSum) {
            maxSum = currentSum;
            *outlength = 1;
            numbersWithMaxSum[0] = array[i];
        } else if (currentSum == maxSum) {
            numbersWithMaxSum[*outlength] = array[i];
            ++(*outlength);
        }
    }
    numbersWithMaxSum = realloc(numbersWithMaxSum, *outlength * sizeof(int));
    return numbersWithMaxSum;
}