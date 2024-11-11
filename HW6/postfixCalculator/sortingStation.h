#pragma once
#include "../../localLibs/queue/queueDeclaration.h"

Queue *sortingMachine(char *infixExpession, int *errorCode);
char *postfixExpressionToString(Queue *postfixExpression);