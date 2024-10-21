#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "biformDeclaration.h"
#include "binAdding.h"

bool validationTest() {
    bool isTestSuccesful = true;
    int countOfTests = 0;
    int countOfSuccesfulTests = 0;

    Biform firstTerm, secondTerm, sum, theOne;
    
    setBiform(&firstTerm, -100000);
    setBiform(&secondTerm, -10000);
    setBiform(&theOne, 1);

    srand(clock());
    while (firstTerm.decimalValue < 100000) {
        while (secondTerm.decimalValue < 10000) {
            if (rand() % 3 > 1) {
                continue;
            }
            sum = binAdd(firstTerm, secondTerm);
            long long correctResult = firstTerm.decimalValue + secondTerm.decimalValue;
            if (sum.decimalValue == correctResult) {
                ++countOfSuccesfulTests;
            } else {
                isTestSuccesful = false;
            }
            secondTerm = binAdd(secondTerm, theOne);
            ++countOfTests;
        }
        firstTerm = binAdd(firstTerm, theOne);
    }
    printf("[%d/%d]", countOfSuccesfulTests, countOfTests);
    puts(isTestSuccesful ? "Test succesfully passed" : "Test failed");

    freeBiform(&firstTerm);
    freeBiform(&secondTerm);
    freeBiform(&sum);
    freeBiform(&theOne);
}