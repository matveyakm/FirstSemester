#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    long long decimalValue; // 64 bits
    bool binaryValue[64];
} Biform;

void setBinaryValue(Biform *number);
void setDecimalValue(Biform *number);
void setBiform(Biform *number, long long decimalValue);
void printBiform(Biform *number);