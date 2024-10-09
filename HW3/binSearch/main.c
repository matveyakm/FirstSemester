#include "../../localLibs/qsort/qsort.h"
#include "../../localLibs/binSearch/binSearch.h"
#include "../../localLibs/testingTools/testingTools.h"
#include <stdio.h>
#ifdef TEST
#include "test.h"
#endif

// Получить с клавиатуры 2 числа, n и k, сгенерировать случайно массив из n чисел, сгенерировать k случайных целых чисел, для каждого из них проверить, содержится ли оно в массиве. Надо придумать алгоритм с временной сложностью O(n log n + k log n), или лучший.

// Странно, что findInArray тратит сильно больше времени, чем find, запущенный в цикле. 

int main() {
    #ifdef TEST
            validationTest();
    #endif
    // RELEASE
    {
        int n, k;
        scanf("%d %d", &n, &k); // не ломайте мой код, пжпж
        int *array = malloc(n * sizeof(int));
        int *targetNumbers = malloc(k * sizeof(int));
        randomizeArray(array, n, 0);
        randomizeArray(targetNumbers, k, 0);
        
        puts("Generated array:");
        printArray(array, n);
        puts("Target numbers::");
        printArray(targetNumbers, k);
        
        qsorting(array, n);
        qsorting(targetNumbers, k);

        puts("\nAfter sorting:");
        printArray(array, n);
        printArray(targetNumbers, k);
        
        puts("\nIndexes of target number in array:");
        for (int i = 0; i < k; i++) {
            printf("%d ", qfind(targetNumbers[i], array, n));
        }
        puts("\n");

        findFromArray(targetNumbers, array, k, n);     
        printArray(targetNumbers, k);
        

        free(array);
        free(targetNumbers);
    }

}