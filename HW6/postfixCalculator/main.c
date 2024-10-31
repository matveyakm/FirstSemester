#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortingStation.h"
#include "postfixCalculator.h"

int main () {
    char infix[] = "(1000 + 500) / 3";
    char *postfix = postfixExpressionToString(sortingMachine(infix));
    for (int i = 0; i < strlen(postfix); ++i) {
        printf("%c", postfix[i]);
    }
    puts("");
    printf("%d\n", postfixCalculator(postfix));
    printf("%d\n", postfixCalculator(sortingMachine(infix)));
    printf("%d\n", calculator(infix));
}