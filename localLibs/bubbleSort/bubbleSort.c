#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../arrayFuncs/arrayFuncs.h"


void bubbleSort(int *array, const int arrayLenth) {
    bool wasSwapped = true;
    for (int i = 0; i < arrayLenth; i++) {
        if (!wasSwapped) return;
        wasSwapped = false;
        for (int j = arrayLenth - 1; j > i; j--) {
            if (array[j] < array[j - 1]) {
                swap(&array[j], &array[j - 1]);
                wasSwapped = true;
            }
        }
    }
}