#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Cyclic Cyclic;

// functions that work exclusively for cyclic
Cyclic *createCyclic(int length);
int cyclicLength(Cyclic *cyclic);
void appendC(Cyclic *cyclic, int value);
void pushAtC(Cyclic *cyclic, int position, int value);
int popAtC(Cyclic *cyclic, int position);
int popC(Cyclic *cyclic);
void shiftHead(Cyclic *cyclic, int position);
int *cyclicToArray(Cyclic *cyclic);
Cyclic *arrayToCyclic(int *array, int arrayLength);
void deleteCyclic(Cyclic *cyclic);

// functions that work interchangeably with list functions
int peekAtC(Cyclic *cyclic, int position);
void printCyclic(Cyclic *cyclic);