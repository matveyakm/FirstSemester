#include <stdbool.h>
#include "list/listDeclaration.h"

bool deleteElementsWithOddIndex(List *list) {
    if (!list) {
        return false;
    }
    const int listLength = getListLength(list);
    if (listLength <= 1) {
        return listLength >= 0;
    }
    
    int index = 0;
    bool needSwapParity = true;
    int errorCode = OK;
    while (index < getListLength(list)) {
        if (index % 2 == needSwapParity) {
            popAtL(list, index, &errorCode);
            if (errorCode != OK) {
                return false;
            }
            needSwapParity = !needSwapParity;
        } else {
            index += 1;
        }
    }
    return true;
}