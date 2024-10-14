#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "biformDeclaration.h"

Biform binAdd(Biform firstTerm, Biform secondTerm) {
    int bits = sizeof(long long) * 8; // = 64
    bool *binaryValueResult = malloc(bits * sizeof(bool));

    bool carry = false;
    for (int i = bits - 1; i >= 0; --i) {
        if (firstTerm.binaryValue[i] == secondTerm.binaryValue[i]) {
            binaryValueResult[i] = carry;
            carry = firstTerm.binaryValue[i];
        } else {
            binaryValueResult[i] = !carry;
        }
    }

    Biform result;
    memcpy(result.binaryValue, binaryValueResult, bits * sizeof(bool));
    setDecimalValue(&result);

    free(binaryValueResult);
    return result;
}