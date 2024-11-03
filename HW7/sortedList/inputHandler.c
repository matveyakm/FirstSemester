#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listManager.h"
#include "../../localLibs/list/listDeclaration.h"

void startProccesing() {
    List *sortedList = createList(0);
    bool needToLoop = true;
    while (needToLoop) {
        int action;
        puts("==Enter a command:");
        if (scanf("%d", &action) != 1) {
            puts("===You can only enter a integer number!===\nExiting...\n");
            break; // 
        }
        int value;
        switch (action) {
        case 0:
            needToLoop = false;
            break;

        case 1:
            puts("=Enter a value to add to the list:");
            printf("-");
            if (scanf("%d", &value) != 1) {
                puts("===Input error.");
                break;
            }
            addValue(sortedList, value);
            puts("=Added.");
            break;

        case 2:
            puts("=Enter a value to delete from the list:");
            printf("-");
            if (scanf("%d", &value) != 1) {
                puts("===Input error.");
                break;
            }
            puts(deleteValue(sortedList, value) ? "Deleted" : "Not found.");
            break;

        case 3:
            printf("=");
            printList(sortedList);
            break;

        default:
            puts("\
            0 - exit\n\
            1 - add an element\n\
            2 - delete an element by value\n\
            3 - display the list\n\
            4 - help\n\
            Enter one of this numbers to interact");
            break;
        }
    }
    deleteList(sortedList);
}