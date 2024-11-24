#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"
#include "sortingStation.h"
#define PASSED_EXPESSION_IS_INCORRECT 10
#define PASSED_QUEUE_IS_EMPTY 11

const char expectedSymbols[] = "*+-/ 0123456789";

bool isExpectedSymbol(char token) {
    for (int i = 0; i < strlen(expectedSymbols); ++i) {
        if (token == expectedSymbols[i]) {
            return true;
        }
    }
    return false;
}

Queue *postfixExpressionParser(char *rawPostfixExpression) {
    Queue *queue = createQueue();
    char *string = rawPostfixExpression;
    int stringLength = strlen(rawPostfixExpression);
    for (int i = 0; i < stringLength; ++i) {
        enqueue(queue, string[i]);
    }
    return queue;
}

bool calculate(Stack *operands, char operator) {
    if (isStackEmpty(operands)) {
        return false;
    }
    int tempValue = pop(operands);
    if (isStackEmpty(operands)) {
        return false;
    }
    switch (operator) {
        case '+':
            push(operands, pop(operands) + tempValue);
            return true;
        case '-':
            push(operands, pop(operands) - tempValue);
            return true;
        case '*':
            push(operands, pop(operands) * tempValue);
            return true;
        case '/':
            if (tempValue == 0) {
                return false;
            } else {
                push(operands, pop(operands) / tempValue);
                return true;
            }
        default:
            return false;
        }

}

int queuePostfixCalculator(Queue *postfixExpression, int *errorCode) {
    Stack *operands = createStack(); // it is going to keep numbers in the int form, not in ascii
    bool nextNumberParsing = true;
    bool isQueuePassedEmpty = isQueueEmpty(postfixExpression);
    while(!isQueueEmpty(postfixExpression)) {
        char token = dequeue(postfixExpression); 
        if (isExpectedSymbol(token)) {
            if (token >= '0' && token <= '9') {
                if (nextNumberParsing || isStackEmpty(operands)) {
                    push(operands, (int)token - '0');
                    nextNumberParsing = false;
                } else {
                    push(operands, pop(operands) * 10 + (int)token - '0');
                }
            } else if (token == ' ') {
                nextNumberParsing = true;
            } else {
                nextNumberParsing = true;
                if (!calculate(operands, token)) {
                    *errorCode = PASSED_EXPESSION_IS_INCORRECT;
                    deleteStack(operands);
                    deleteQueue(postfixExpression);
                    return 0;
                }
            }
        }
    }
    if (isStackEmpty(operands)) {
        *errorCode = isQueuePassedEmpty ? PASSED_QUEUE_IS_EMPTY : PASSED_EXPESSION_IS_INCORRECT;
        deleteStack(operands);
        deleteQueue(postfixExpression);
        return 0;
    }
    int resultValue = pop(operands);
    *errorCode = isStackEmpty(operands) ? *errorCode : PASSED_EXPESSION_IS_INCORRECT;
    deleteStack(operands);
    deleteQueue(postfixExpression);
    return errorCode == PASSED_EXPESSION_IS_INCORRECT ? 0 : resultValue;
}

int stringPostfixCalculator(char *rawPostfixExpression, int *errorCode) {
    Queue *postfixExpression = postfixExpressionParser(rawPostfixExpression);
    return queuePostfixCalculator(postfixExpression, errorCode);
}

int calculator(char *infixExpression, int *errorCode) {
    Queue *postfixQueue = sortingMachine(infixExpression, errorCode);
    return queuePostfixCalculator(postfixQueue, errorCode);
}