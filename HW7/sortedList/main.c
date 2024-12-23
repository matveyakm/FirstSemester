#include <stdio.h>
#include "inputHandler.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    puts("Testing...");
    if (!validationTest(10)) {
        puts("Test failed.");
        return 1;
    } else {
        puts("Ready to process.");
    }
    #endif
    startProccesing();
}
