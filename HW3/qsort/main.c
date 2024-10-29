#include <stdio.h>
#include <stdlib.h>
#include "../../localLibs/testingTools/testingTools.h"
#include "smartQSort.h"
#ifdef TEST
#include "test.h"
#endif

// Реализовать qsort, который для сортировки кусков массива размером меньше 10 использует сортировку вставкой. Поскольку qsort делит массив на части и сортирует каждую qsort-ом же, можно добиться заметного ускорения, если совсем уж маленькие части сортировать квадратичной сортировкой с меньшей константой. Эту идею и надо реализовать.

int main() {
     #ifdef TEST
    if (!validationTest(false)) {
        return 1;
    }
    #endif  

    const int arrayLength = 20;
    int *array = malloc(arrayLength * sizeof(int));
    
    randomizeArray(array, arrayLength, 0);
    printArray(array, arrayLength);
    
    smartQSorting(array, arrayLength);
    printArray(array, arrayLength);
}