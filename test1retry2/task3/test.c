#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "commentDetector.h"

bool validationTest(char *fileName) {
    char correctAnswer[] = ";54321\n; ABC\n; 1 2 3\n; hello world\n;\n;";
    char *comments = getCommentsFromFile(fileName);

    bool isTestSuccessful = strcmp(correctAnswer, comments) == 0;
    free(comments);
    return isTestSuccessful;
}