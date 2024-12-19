#include <stdio.h>
#include "dictionary.h"
#include "IOHandler.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest()) {
        puts("Something went wrong.");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    startInterfaceProcessing();
}