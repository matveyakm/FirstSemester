#include "inputHandler.h"
#include "listManager.h"
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