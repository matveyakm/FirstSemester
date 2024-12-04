#include <stdio.h>
#include "dictionary.h"

int main() {
    Dictionary *dict = createDictionary();
    addPairToDict(dict, 10, "Lada");
    addPairToDict(dict, 9, "Kama");
    printDictionary(dict);
}