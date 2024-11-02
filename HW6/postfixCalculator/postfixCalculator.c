#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"
#include "sortingStation.h"

bool isString(void *container) { // =)
    if (container == NULL) {
        return false;
    }
    char *str = (char *)container;
    while (*str) {  
        if (*str < 32 || *str > 126) {
            return false;
        }
        str++;
    }
    return true; 
}

const char expectedSymbols[] = "*+-/ 0123456789";

bool isExpectedSymbol(char token) {
    for (int i = 0; i < strlen(expectedSymbols); ++i) {
        if (token == expectedSymbols[i]) {
            return true;
        }
    }
    return false;
}

Queue *postfixExpressionParser(void *rawPostfixExpression) {
    if (!isString(rawPostfixExpression)) {
        return (Queue *)rawPostfixExpression;
    }
    Queue *queue = createQueue();
    char *string = (char *)rawPostfixExpression;
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
                puts("Division by zero.");
                return false;
            } else {
                push(operands, pop(operands) / tempValue);
                return true;
            }
        default:
            return false;
        }

}

int postfixCalculator(void *rawPostfixExpression) {
    Queue *postfixExpression = postfixExpressionParser(rawPostfixExpression);
    Stack *operands = createStack(); // it is going to keep numbers in the int form, not in ascii
    bool nextNumberParsing = true;
    bool isQueuePassedEmpty = isQueueEmpty(postfixExpression);
    while(!isQueueEmpty(postfixExpression)) {
        char token = dequeue(postfixExpression); 
        if (isExpectedSymbol(token)) {
            if (token >= '0' && token <= '9') {
                if (nextNumberParsing || isStackEmpty(operands)) {
                    push(operands, (int)token - 48);
                    nextNumberParsing = false;
                } else {
                    push(operands, pop(operands) * 10 + (int)token - 48);
                }
            } else if (token == ' ' ) {
                nextNumberParsing = true;
            } else {
                nextNumberParsing = true;
                if (!calculate(operands, token)) {
                    puts("Calculation failed. ERR=10");
                    deleteStack(operands);
                    deleteQueue(postfixExpression);//
                    return 0;
                }
            }
        }
    }
    if (isStackEmpty(operands)) {
        puts(isQueuePassedEmpty ? "Calculation failed. ERR=111" : "Calculation failed. ERR=110");
        deleteStack(operands);
        deleteQueue(postfixExpression);//
        return 0;
    }
    int resultValue = pop(operands);
    if (!isStackEmpty(operands)) {
        puts("Calculation failed. ERR=12");
        deleteStack(operands);
        deleteQueue(postfixExpression);//
        return 0;
    } else {
        deleteStack(operands);
        deleteQueue(postfixExpression);//
        return resultValue;
    }
}

int calculator(char *infixExpression) {
    Queue *postfixQueue = sortingMachine(infixExpression);
    return postfixCalculator(postfixQueue);
}