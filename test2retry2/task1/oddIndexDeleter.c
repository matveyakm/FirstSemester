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
    bool needOdd = true;
    int errorCode = OK;
    while (index < getListLength(list)) {
        //printf("%d:", index);
        //printList(list);
        if (index % 2 == needOdd) {
            //printf("DELETED |%d|\n", peekL(list, index, &errorCode));
            popAtL(list, index, &errorCode);
            if (errorCode != OK) {
                return false;
            }
            needOdd = !needOdd;
        } else {
            index += 1;
        }
    }
    return true;
}