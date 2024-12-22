#include <stdio.h>
#include <stdbool.h>
#include "fileManager.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest()) {
        puts("Test failed.");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    if (processFile("f_file.txt", "g_file.txt", 4, 7) == OK) {
        puts("Processed: f --> g");
    }
}