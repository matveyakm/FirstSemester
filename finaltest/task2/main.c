#include <stdio.h>
#include "queue.h"
#ifdef TEST
#include "test.h"
#define TEST_FAILED 50
#endif

int main() {
    #ifdef TEST
    if (!validationTest()) {
        puts("Something went wrong.");
        return TEST_FAILED;
    } else {
        puts("Ready to process.");
    }
    #endif

    Queue *q = createQueue();
    int errorCode = 0;
    enqueue(q, 10, &errorCode);
    enqueue(q, 20, &errorCode);
    enqueue(q, 30, &errorCode);
    printf("%d\n", peekQueue(q, &errorCode));
    printf("%d\n", dequeue(q, &errorCode));
    printf("%d\n", dequeue(q, &errorCode));
    enqueue(q, 40, &errorCode);
    printf("%d\n", dequeue(q, &errorCode));
    printf("%d\n", dequeue(q, &errorCode));
}