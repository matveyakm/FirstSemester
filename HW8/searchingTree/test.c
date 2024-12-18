#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"
#include "../../localLibs/testingTools/testingTools.h"

char *convertIntToString(int integer) {
    int maxCountOfCharsInInt = 8 * sizeof(int);
    char *string = malloc(maxCountOfCharsInInt * sizeof(char));
    sprintf(string, "%d", integer);
    return string;
}

int convertStringToInt(char *string) {
    int result = 0;
    while (*string) {
        result = result * 10 + (*string - '0');
        string++;
    }
    return result;
}

bool validationTest(void) {
    bool isTestSuccessful = true;
    Dictionary *dictionary = createDictionary();
    int arrayLength = 1024;
    int *randomArray = malloc(arrayLength * sizeof(int));
    randomizeArrayInRange(randomArray, arrayLength, 0, 0, 1000);

    for (int i = 0; i < arrayLength; ++i) {
        char *stringForm = convertIntToString(randomArray[i]);
        addPairToDict(dictionary, randomArray[i], stringForm);
        free(stringForm);
    }

    for (int i = 0; i < arrayLength; ++i) {
        isTestSuccessful *= convertStringToInt(getDataByKey(dictionary, randomArray[i])) == randomArray[i];
    }
    deleteDictionary(dictionary);
    free(randomArray);
    return isTestSuccessful;
}
