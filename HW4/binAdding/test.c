#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "biformDeclaration.h"
#include "binAdding.h"

bool validationTest() {
    puts("Wait a few minutes. Testing...");
    bool isTestSuccesful = true;
    unsigned long long countOfTests = 0;
    unsigned long long countOfSuccesfulTests = 0;

    Biform firstTerm, secondTerm, sum, theOne;
    
    setBiform(&firstTerm, -10000);
    setBiform(&theOne, 1);

    while (firstTerm.decimalValue < 10000) {
        setBiform(&secondTerm, -1000);
        while (secondTerm.decimalValue < 1000) {
            srand(clock());
            if (rand() % 12113 > 0) {
                secondTerm = binAdd(secondTerm, theOne);
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
}