#include <stdio.h>
#include <string.h>
#include "../../localLibs/trees/binTree.h"
#include "IOHandler.h"
#include "expressionCalculator.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest("parsingTreeTest.txt")) {
        puts("Something went wrong.");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    char *expression = strdup("+ 2 3");
    binTreeNode *root = parseExpression(expression);
    printExpression(root);
    printf("%d\n", calculateValue(root));
}