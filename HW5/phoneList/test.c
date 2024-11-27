#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "noteManager.h"
#include "inputHandler.h"

bool test1(void) {
    bool isTestSuccessful = true;
    Note *notes = malloc(MAX_COUNT_OF_NOTES * sizeof(Note));
    for (int i = 0; i < MAX_COUNT_OF_NOTES; ++i) {
        char name[128] = "";
        name[0] = (char)i;
        Note newNote = makeNote(name, i);
        notes[i] = newNote;
    }
    for (int i = 0; i < MAX_COUNT_OF_NOTES; ++i) {
        char name[128] = "";
        name[0] = (char)i;
        long foundPhoneNumber = findPhoneNumber(notes, MAX_COUNT_OF_NOTES, name);
        isTestSuccessful *= foundPhoneNumber == i;
    }
    for (int i = 0; i < MAX_COUNT_OF_NOTES; ++i) {
        char name[128] = "";
        name[0] = (char)i;
        char *foundName = findName(notes, MAX_COUNT_OF_NOTES, i);
        isTestSuccessful *= strcmp(foundName, name) == 0;
    }
    
    free(notes);
    return isTestSuccessful;
}

bool test2(char *testFileName) {
    bool isTestSuccessful = true;
    int countOfNotes;
    bool loadedSuccessfully;
    Note *notes = loadFromFile(testFileName, &countOfNotes, &loadedSuccessfully);
    if (!loadedSuccessfully) {
        return true;
    }
    isTestSuccessful *= countOfNotes == 15;
    {
        isTestSuccessful *= findPhoneNumber(notes, countOfNotes, "Lada") == 999;
        isTestSuccessful *= findPhoneNumber(notes, countOfNotes, "ALBLACK") == 52;
        isTestSuccessful *= findPhoneNumber(notes, countOfNotes, "McLaren") == 720;
        isTestSuccessful *= findPhoneNumber(notes, countOfNotes, "NULLNAME") == -1;
        isTestSuccessful *= findPhoneNumber(notes, countOfNotes, "Zxcursed") == 14000;
    }
    {
        isTestSuccessful *= strcmp(findName(notes, countOfNotes, 911), "Twins") == 0;
        isTestSuccessful *= strcmp(findName(notes, countOfNotes, 228), "Abed") == 0;
        isTestSuccessful *= strcmp(findName(notes, countOfNotes, 5051), "IvanPoh") == 0;
        isTestSuccessful *= strcmp(findName(notes, countOfNotes, 666), "Kama") == 0;
        isTestSuccessful *= strcmp(findName(notes, countOfNotes, 999), "Lada") == 0;
        isTestSuccessful *= strcmp(findName(notes, countOfNotes, 101), "Lenin") != 0;
    }
    free(notes);
    return isTestSuccessful;
}

bool validationTest(char *testFileName) {
    return test1() * test2(testFileName);
}