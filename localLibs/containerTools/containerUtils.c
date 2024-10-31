#include "containerUtils.h"
#include "../stack/stackDeclaration.h"
#include "../queue/queueDeclaration.h" 

bool isEmpty(void *container) {
    /*
    if (isStack(container)) {
        return stackIsEmpty((Stack *)container);
    } else if (isQueue(container)) {
        return queueIsEmpty((Queue *)container);
    }
    return true;*/
}

int peek(void *container) {
    /*
    if (isStack(container)) {
        return stackPeek((Stack *)container);
    } else if (isQueue(container)) {
        return queuePeek((Queue *)container);
    }*/
    return -1; 
}
