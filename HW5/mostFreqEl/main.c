#include <stdio.h>
#include <stdlib.h>
#include "../../HW3/mostFreqElement/findingMostFreqElement.h"
#include "../../localLibs/testingTools/testingTools.h"
#include "../../localLibs/qsort/qsort.h"
#include "fileReader.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!fileValidationTest(20)) {
        return 1;
    }
    #endif

    int arrayLength;
    int *array = loadFile("array.txt", &arrayLength);
    
    printArray(array, arrayLength);

    qsorting(array, arrayLength);
    printArray(array, arrayLength);

    printf("%d\n", findForMostFreqElement(array, arrayLength));

    free(array);   
}