#include <stdio.h>
#include "commentDetector.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest("commentTaskTest.txt")) {
        puts("Test failed.");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    puts("== Comments from your file:");
    printCommentsFromFile("commentTask.txt");
}