#include <stdio.h>
#include "../../localLibs/list/pointerList.h"
#include "noteManager.h"
#include "IOHandler.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    puts("Testing...");
    if (validationTest(5)) {
        puts("Ready to process.");
    } else {
        puts("Test failed. Exiting...");
        return 1;
    }
    #endif

    startProcessing("phonebook.txt");
}