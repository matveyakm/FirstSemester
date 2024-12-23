#include <stdio.h>
#include "list/listDeclaration.h"
#include "oddIndexDeleter.h"
#ifdef TEST
#include "test.h"
#endif

int main() {
    #ifdef TEST
    if (!validationTest(5)) {
        puts("Test failed");
        return TEST;
    } else {
        puts("Ready to process.");
    }
    #endif

    List *list = createList(0);
    if (!list) {
        return ALLOCATION_ERROR;
    }

    int errorCode = OK;
    for (int i = 0; i < 10; ++i) {
        appendL(list, i, &errorCode);
    }

    printList(list);
    puts(deleteElementsWithOddIndex(list) ? "Processed" : "Something went wrong");

    printList(list);
}