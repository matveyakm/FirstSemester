#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../binSearch/binSearch.h"

void randomizeArray(int *arrayNeedToRandomize, int arrayLength, int seed);
void randomizeArrayInRange(int *arrayNeedToRandomize, int arrayLength, int seed, int low, int high);
void randomizeSet(int *arrayNeedToRandomize, int arrayLength, int seed);
void randomizeSetInRange(int *arrayNeedToRandomize, int arrayLength, int seed, int low, int high);

void printArray(int *arrayNeedToPrint, int arrayLength);
double convertTime(clock_t time);