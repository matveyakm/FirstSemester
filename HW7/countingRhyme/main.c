#include <stdio.h>
#include <stdbool.h>
#include "../../localLibs/list/cyclicList.h"
#define TEST_FAILED 52

// ===== !!! =====
// The decision is controversial. Be critical.
// ===== !!! =====

int findK(int n, int m) {
    Cyclic *warriors = createCyclic(0);
    for (int i = 0; i < n; ++i) {
        appendC(warriors, i);
    }
    int i = 0;
    int chainCounter = 1;
    while (cyclicLength(warriors) > 1) {
        if (chainCounter % m == 0) {
            popAtC(warriors, i);
            --i;
            chainCounter = 1;
        } else {
            ++chainCounter;
        }
        i = (i + 1) % cyclicLength(warriors);
    }
    int k = peekC(warriors, 0);
    clearCyclic(warriors);
    return k;
}

bool validationTest(void) {
    bool isTestSuccesful = true;
    isTestSuccesful *= findK(5, 3) == 4;
    isTestSuccesful *= findK(13, 3) == 12;
    isTestSuccesful *= findK(7, 2) == 6;
    isTestSuccesful *= findK(11, 4) == 8;
    isTestSuccesful *= findK(6, 4) == 4;
    isTestSuccesful *= findK(11, 3) == 6;
    isTestSuccesful *= findK(9, 8) == 2;
    isTestSuccesful *= findK(9, 1) == 8;
    return isTestSuccesful;
}

int main() {
    #ifdef TEST
    if (!validationTest()) {
        puts("Test failed.");
        return TEST_FAILED;
    } else {
        puts("Ready to process.");
    }
    #endif

    int n, m;
    puts("Enter n, m:");
    scanf("%d %d", &n, &m);
    printf("k = %d\n", findK(n, m));
}
