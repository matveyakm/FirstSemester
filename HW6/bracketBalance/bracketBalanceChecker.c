#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../localLibs/stack/stackDeclaration.h"

bool isPair(char opening, char ending) {
    bool result = false;
    result += opening == '(' && ending == ')';
    result += opening == '{' && ending == '}';
    result += opening == '[' && ending == ']';
    return result;
}

bool areBracketsBalanced(char *string) {
    Stack *brackets = createStack();
    int stringLength = strlen(string);
    for (int i = 0; i < stringLength; ++i) {
        if (string[i] == '(' || string[i] == '{' || string[i] == '[') {
            push(brackets, string[i]);
            //printf("ADDED %c\n", peek(brackets));
        } else if (string[i] == ')' || string[i] == '}' || string[i] == ']') {
            //printf("DELETED %c\n", peek(brackets));
            if (isEmpty(brackets) || !isPair((char)pop(brackets), string[i])) {
                deleteStack(brackets);
                //puts("EX");
                return false;
            }
        } else {
            //printf("IGNORED %c\n", string[i]);
        }
    }

    bool areThereBracketsWithoutPair = !isEmpty(brackets);
    deleteStack(brackets); 
    return !areThereBracketsWithoutPair;
}