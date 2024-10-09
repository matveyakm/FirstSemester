#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

const bool isArraySorted(int *arrayNeedToCheck, const int arraysLenth) {
    bool isTestSucceful = true;
    for (int i = 1; i < arraysLenth; i++) {
        if (arrayNeedToCheck[i-1] > arrayNeedToCheck[i]) {
            isTestSucceful = false;
        }
    }
    return isTestSucceful;
}