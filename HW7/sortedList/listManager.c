#include <stdlib.h>
#include <stdbool.h>
#include "../../localLibs/list/listDeclaration.h"

void addValue(List *sortedList, int value) {
    int searchingIndex = 0;
    while (searchingIndex < listLength(sortedList) && peekAt(sortedList, searchingIndex) < value) {
        ++searchingIndex;
    }
    pushAt(sortedList, searchingIndex, value);
}

bool deleteValue(List *sortedList, int value) {
    for (int i = 0; i < listLength(sortedList); ++i) {
        if (peekAt(sortedList, i) == value) {
            popAt(sortedList, i);
            return true;
        }
    }
    return false;
}