#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "biformDeclaration.h"

Biform binAdd(Biform firstTerm, Biform secondTerm) {
    int bits = sizeof(long long) * 8; // = 64
    Biform result;
    result.binaryValue = malloc(bits * sizeof(bool));

    bool carry = false;
    for (int i = bits - 1; i >= 0; --i) {
        if (firstTerm.binaryValue[i] == secondTerm.binaryValue[i]) {
            result.binaryValue[i] = carry;
            carry = firstTerm.binaryValue[i];
        } else {
            result.binaryValue[i] = !carry;
        }
    }

    setDecimalValue(&result);

    return result;
}