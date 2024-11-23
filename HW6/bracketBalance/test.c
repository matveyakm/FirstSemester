#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../../localLibs/testingTools/testingTools.h"
#include "bracketBalanceChecker.h"

bool noStackMethod(char *string) {
    int stringLength = strlen(string);

    int countOfRoundBrackets = 0;
    int countOfCurlyBrackets = 0;
    int countOfSquareBrackets = 0;

    for (int i = 0; i < stringLength; ++i) {
        switch (string[i]) {
        case '(':
            ++countOfRoundBrackets;
            break;
        case ')':
            --countOfRoundBrackets;
            break;
        case '{':
            ++countOfCurlyBrackets;
            break;
        case '}':
            --countOfCurlyBrackets;
            break;
        case '[':
            ++countOfSquareBrackets;
            break;
        case ']':
            --countOfSquareBrackets;
            break;
        default:
            break;
        }
        if (countOfCurlyBrackets * countOfRoundBrackets * countOfSquareBrackets < 0) {
            return false;
        }
    }
    return countOfCurlyBrackets + countOfRoundBrackets + countOfSquareBrackets == 0;
}

bool defaultTest() { // compare with prefilled
    bool isTestSuccesful = true;
    isTestSuccesful *= areBracketsBalanced("");
    isTestSuccesful *= areBracketsBalanced("0");
    isTestSuccesful *= areBracketsBalanced("{}[]{[()]}");
    isTestSuccesful *= areBracketsBalanced("($(((0((($())4)))1))?)");
    isTestSuccesful *= areBracketsBalanced("([()()([()]){[()[()]]}[[({[([])]})]]])");
    isTestSuccesful *= areBracketsBalanced("((z[|=_=|][{([sta]riy)}boh])52)[]b{{([vanya[]](pox)[({a})])}}");
    isTestSuccesful *= !areBracketsBalanced("([]{([]{}[{()[]([])}[]}])}([[]{}]))[]");
    isTestSuccesful *= !areBracketsBalanced("abcdef_()[]zxc[({)})]($$$)[()]");
    isTestSuccesful *= !areBracketsBalanced("({)}");
    return isTestSuccesful;
}

void randomFillingString(char *string, char *alphabet) {
    int *pattern = malloc(strlen(string) * sizeof(int));
    randomizeArrayInRange(pattern, strlen(string), 0, 0, strlen(alphabet) - 1);
    for (unsigned int fillingIndex = 0; fillingIndex < strlen(string); ++fillingIndex) {
        string[fillingIndex] = alphabet[pattern[fillingIndex]];
    }
    free(pattern);
}

bool validationTest(int countOfTests) {
    bool isTestSuccesful = defaultTest();

    int stringLength = 1000;
    char *string = malloc(stringLength * sizeof(char)); 
    
    for (int i = 0; i < countOfTests / 2; ++i) {
        randomFillingString(string, "(){}[]abc0.123");
        isTestSuccesful *= areBracketsBalanced(string) <= noStackMethod(string);
    }

    for (int i = 0; i < countOfTests / 2; ++i) {
        randomFillingString(string, "()");
        isTestSuccesful *= areBracketsBalanced(string) == noStackMethod(string);
    }

    free(string);

    puts(isTestSuccesful ? "Test successfully passed." : "Test failed.");
    return isTestSuccesful;
}