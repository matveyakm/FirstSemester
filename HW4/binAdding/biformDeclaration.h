#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
//#include "../../localLibs/arrayFuncs/arrayFuncs.c"

typedef struct{
    long long decimalValue; // 64 bits
    bool *binaryValue;
} Biform;

void setBinaryValue(Biform *number);
void setDecimalValue(Biform *number);
void setBiform(Biform *number, long long decimalValue);
void printBiform(Biform *number);
void freeBiform(Biform *number);