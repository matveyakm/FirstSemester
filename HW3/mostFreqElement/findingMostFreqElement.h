#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../localLibs/arrayFuncs/arrayFuncs.h"
#include "../../localLibs/testingTools/testingTools.h"

int findForMostFreqElement(int *array, int arrayLength);

// ===== not recommended for usage. only for experiment
int linearFindForMostFreqElement(int *array, int arrayLength);
int quadraticFindForMostFreqElement(int *array, int arrayLength);
int findForMostFreqElementByCounting(int *array, int arrayLength);