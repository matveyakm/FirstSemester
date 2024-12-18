#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

char *getData(void) {
    char string[128] = "empty";
    scanf("%127s", string);
    char *data = malloc(strlen(string) * sizeof(char));
    strcpy(data, string);
    return data;
}

int getKey(void) {
    int key = -52;
    scanf("%d", &key);
    return key;
}

void startInterfaceProcessing(void) {
    Dictionary *dict = createDictionary();
    while (true) {
        puts("==Enter a command:");
        int action = 52;
        scanf("%d", &action);
        int key = -52;
        switch (action) {
        case 0:
            deleteDictionary(dict);
            return;
        
        case 1:
            puts("=Enter a key:");
            key = getKey();
            puts("=Enter a data:");
            char *data = getData();
            addPairToDict(dict, key, data);
            free(data);
            break;

        case 2:
            puts("=Enter a key:");
            key = getKey();
            printf("-%d: %s\n", key, getDataByKey(dict, key));
            break;

        case 3:
            puts("=Enter a key:");
            key = getKey();
            puts(isPairExist(dict, key) ? "This pair exists." : "This pair is not exist.");
            break;

        case 4:
            puts("=Enter a key:");
            key = getKey();
            clearPair(dict, key);
            break;

        case 5:
            printDictionary(dict);
            break;

        default:
            puts("\
             0 - exit\n\
             1 - add pair to dictionary\n\
             2 - get data by key\n\
             3 - find out if a pair exists\n\
             4 - clear pair by key\n\
             5 - print all pairs\n\
             Enter one of this numbers to interact");
            break;
        }
    }
    deleteDictionary(dict);
}