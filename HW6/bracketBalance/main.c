#include <stdio.h>
#include <stdlib.h>
#include "bracketBalanceChecker.h"
#ifdef TEST
#include "test.h"
#endif


int main() {
    #ifdef TEST
    if (!validationTest(100000)) {
        return 1;
    }
    #endif

    char inputString[128];
    puts("-Enter a string:");
    fgets(inputString, sizeof(inputString), stdin);
    puts(areBracketsBalanced(inputString) ? "-Brackets are balanced in this string." : "-Brackets are not balanced in this string.");
}