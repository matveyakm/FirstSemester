#pragma once
#include "../../localLibs/list/listDeclaration.h"
#include <stdbool.h>

void addValue(List *sortedList, int value);
bool deleteValue(List *sortedList, int value);