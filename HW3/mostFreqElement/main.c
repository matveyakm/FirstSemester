#include <stdio.h>
#include <stdlib.h>
#include "findingMostFreqElement.h"
#include "../../localLibs/qsort/qsort.h"
#include "../../localLibs/testingTools/testingTools.h"
#ifdef TEST
#include "test.h"
#endif

// Найти наиболее часто встречающийся элемент в массиве быстрее, чем за O(n^2). Если таких элементов несколько, надо вывести любой из них.

int main() {
    int array[] = {0, 4, 1, 4, 8, 7, 2, 8, 7, 8};
    int arrayLength = sizeof(array) / sizeof(array[0]);

    puts("Array:");
    printArray(array, arrayLength);

    puts("\nAfter sorting:");
    qsorting(array, arrayLength);
    printArray(array, arrayLength);

    printf("\nThe most frequent element in array is %d\n", findForMostFreqElement(array, arrayLength));

    #ifdef TEST
    validationTest();
    #endif  
}