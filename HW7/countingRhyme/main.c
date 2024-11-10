#include <stdio.h>
#include <stdbool.h>
#include "../../localLibs/list/cyclicList.h"

int findK(int n, int m) {
    Cyclic *warriors = createCyclic(0);
    for (int i = 0; i < n; ++i) {
        appendC(warriors, i);
    }
    int i = 0;
    int chainCounter = 1;
    printCyclic(warriors); //
    while (cyclicLength(warriors) > 1) {
        if (chainCounter % m == 0) {
            //printf("DEL %d (%d)\n", i, cyclicLength(warriors));
            popAtC(warriors, i);
            printCyclic(warriors); //
            --i;
            chainCounter = 1;
        } else {
            ++chainCounter;
        }
        ++i;
    }
    int k = peekC(warriors, 0);
    clearCyclic(warriors);
    return k;
}

int main() {
    int n = 5;
    int m = 3;
    printf("%d\n", findK(n, m));
}