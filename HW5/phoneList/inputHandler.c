#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "noteManager.h"

bool savingOnDiskDebuger() {
    puts("===There may have been problems writing the file to disk. Please check its contents.");
    puts("===If all notes you expected to find are there print OK else print MISTAKE");
    char action[52];
    scanf("%s", &action);
    return strcmp(action, "OK") == 0;
}

void startProcessing(char *fileName) {
    int countOfNotesOnDisk;
    int countOfTempNotes = 0;
    Note *notes = loadFromFile(fileName, &countOfNotesOnDisk);

    bool needToLoop = true;
    while (needToLoop) {
        int action;
        printf("==Enter a command: ");
        if (scanf("%d", &action) != 1) {
            puts("===You can only enter a integer number!===\nExiting...\nTrying to save notes to the disk...\n");
            puts(saveToDisk(fileName, notes, countOfNotesOnDisk + countOfTempNotes) ? "Notes saved." : "Saving failed.");
            break; // 
        }
        switch (action) {
        case 0:
            needToLoop = false;
            break;

        case 1:
            if (countOfNotesOnDisk + countOfTempNotes < 100) {
                puts("=Enter a name and a phone number to save it to temporary memory:");
                countOfTempNotes += addNote(notes, countOfTempNotes + countOfNotesOnDisk);;
            } else {
                puts("=No memory to keep a new note.");
            }
            break;

        case 2:
            displayNotes(notes, countOfNotesOnDisk, countOfTempNotes);
            break;

        case 3:
            puts("=Enter a name to find phone number: ");
            long number = findPhoneNumber(notes, countOfNotesOnDisk + countOfTempNotes);
            if (number != -1) {
                printf("-It is %ld.\n", number);
            } else {
                puts("-There is no phone number corresponding to the entered name in base.");
            }
            break;

        case 4:
            puts("=Enter a phone number to find its owner name: ");
            char *name = findName(notes, countOfNotesOnDisk + countOfTempNotes);
            if (strlen(name) > 1) {
                printf("-It is %s.\n", name);
            } else {
                puts("=There is no name corresponding to the entered phone number in base.");
            }
            break;

        case 5:
            puts("=Saving notes to the disk...");
            if (saveToDisk(fileName, notes, countOfNotesOnDisk + countOfTempNotes) || savingOnDiskDebuger()) {
                countOfNotesOnDisk += countOfTempNotes;
                countOfTempNotes = 0;
                puts("=Saved.");
            } else {
                puts("===Try again.");
            }
            break;

        case 6:
            puts("\
            0 - exit\n\
            1 - add new note to temporary memory\n\
            2 - display notes\n\
            3 - find phone number by name\n\
            4 - find name by phone number\n\
            5 - save notes from temporary memory to disk\n\
            Enter one of this numbers to interact");
            break;

        default:
            puts("=It is not an availabel action. Enter '6' to help");
            break;
        }
    }
}