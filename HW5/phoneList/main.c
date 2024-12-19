#include <stdio.h>
#include "inputHandler.h"
#ifdef TEST
#include "test.h"
#define TEST_FAILED 52
#endif


int main() {
    #ifdef TEST
    if (!validationTest("phoneListTest.txt")) {
        puts("Test failed.");
        return TEST_FAILED;
    } else {
        puts("Ready to process.");
    }
    #endif
    startProcessing("./notebook.txt");
}