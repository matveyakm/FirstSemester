#pragma once
#include <stdio.h>
#include <stdlib.h>
#define CYCLIC_INCLUDED

typedef struct Cyclic Cyclic;

// functions that work exclusively for cyclic
Cyclic *createCyclic(int length);
int cyclicLength(Cyclic *cyclic);
void appendC(Cyclic *cyclic, int value);
void addC(Cyclic *cyclic, int position, int value);
int popAtC(Cyclic *cyclic, int position);
int popC(Cyclic *cyclic);
void shiftHead(Cyclic *cyclic, int shift);
int *cyclicToArray(Cyclic *cyclic);
Cyclic *arrayToCyclic(int *array, int arrayLength);
void clearCyclic(Cyclic *cyclic);

// functions that work interchangeably with list functions
int peekC(Cyclic *cyclic, int position);
void printCyclic(Cyclic *cyclic);