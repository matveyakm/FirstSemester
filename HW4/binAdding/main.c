#include <stdio.h>
#include "biformDeclaration.h"
#include "binAdding.h"
//#ifdef TEST
#include "test.h"
//#endif

int main() {
    #ifdef TEST
    validationTest();
    #endif

    Biform firstTerm, secondTerm, result;

    scanf("%lld %lld", &firstTerm.decimalValue, &secondTerm.decimalValue); // не ломайте мой код, пжпж

    setBinaryValue(&firstTerm);
    setBinaryValue(&secondTerm);

    printBiform(&firstTerm);
    printBiform(&secondTerm);

    result = binAdd(firstTerm, secondTerm);

    puts("");
    printBiform(&result);
    puts("");

    printf(" %lld", (firstTerm.decimalValue + secondTerm.decimalValue)); // pointer prosrali

    freeBiform(&firstTerm);
    freeBiform(&secondTerm);
    freeBiform(&result);
}