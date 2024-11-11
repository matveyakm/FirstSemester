#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortingStation.h"
#include "postfixCalculator.h"
#ifdef TEST
#include "test.h"
#endif

int main () {
    #ifdef TEST
    validationTest("postfixTests.txt");
    #endif
    int errorCode = 0;
    char infix[] = "(1000 + 500) / 3";
    printf("Infix: %s\n\n", infix);

    char *postfix = postfixExpressionToString(sortingMachine(infix, &errorCode));
    printf("Postfix: %s\n\n", postfix);

    printf("With passing string: %d\n", stringPostfixCalculator(postfix, &errorCode));
    printf("With passing Queue: %d\n", queuePostfixCalculator(sortingMachine(infix, &errorCode), &errorCode));
    printf("With passing infix: %d\n", calculator(infix, &errorCode));
}