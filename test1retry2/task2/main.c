#include <stdio.h>
#include "selectionSort.h"
#ifdef TEST
#include "test.h"
#endif

#define COUNT_OF_ELEMENTS 10

int main() {
    #ifdef TEST
    if (!validationTest(10)) {
        puts("Test failed.");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    int array[COUNT_OF_ELEMENTS] = {0};
    for (int i = 0; i < COUNT_OF_ELEMENTS; ++i) {
        scanf("%d", &array[i]);
    }

    selectionSort(array, COUNT_OF_ELEMENTS);
    
    for (int i = 0; i < COUNT_OF_ELEMENTS; ++i) {
        printf("%d ", array[i]);
    }
}