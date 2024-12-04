#include <stdio.h>
#include "textAnalyzer.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest(10)) {
        puts("Test failed.");
        return 1;
    } else {
        puts("Ready to process.");
    }
    #endif

    printWordFrequencies("testHash.txt");
}
