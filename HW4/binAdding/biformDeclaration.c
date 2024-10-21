#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "biformDeclaration.h"

void setBinaryValue(Biform *number) {
    int bits = sizeof(long long) * 8; // = 64
    number->binaryValue = malloc(bits * sizeof(bool));

    unsigned long long decimalValueCopy = number->decimalValue;
    if (number->decimalValue < 0) { // convertation to twos complement
        decimalValueCopy = (~(-number->decimalValue)) + 1;
    }
    for (int i = 0; i < bits; ++i) {
        number->binaryValue[bits - i - 1] = decimalValueCopy & 1; // copying bit
        decimalValueCopy >>= 1;
    }
}

void setDecimalValue(Biform *number) {
    int bits = sizeof(long long) * 8; // = 64
    number->decimalValue = 0;
    for (int i = 0; i < bits; ++i) {
        number->decimalValue <<= 1;
        number->decimalValue = number->decimalValue | (int)number->binaryValue[i];
    }
}

void setBiform(Biform *number, long long decimalValue) {
    number->decimalValue = decimalValue;
    setBinaryValue(number);
}

void printBiform(Biform *number) {
    int bits = sizeof(long long) * 8; // = 64
    printf("d%lld\nb", number->decimalValue);
    for (int i = 0; i < bits; ++i) {
        printf("%d", number->binaryValue[i]);
    }
    puts("");
}

void freeBiform(Biform *number) { // error
    number->decimalValue = 0;
    free(number->binaryValue);
}