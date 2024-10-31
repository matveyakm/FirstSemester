#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"
#include "../../localLibs/binSearch/binSearch.h"
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

const char expectedSymbols[] = " *+-/0123456789";

Stack *postfixExpressionParser(void *rawPostfixExpression) {
    if (!isString(rawPostfixExpression)) {
        return (Queue *)rawPostfixExpression;
    }
    Queue *queue = createQueue();
    char *string = (char *)rawPostfixExpression;
    int stringLength = strlen(rawPostfixExpression);
    for (int i = 0; i < stringLength; ++i) {
        if (isIn(string[i], expectedSymbols, strlen(expectedSymbols))) { // err
            enqueue(queue, string[i]);
        }
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
            push(operands, pop(operands) - tempValue);//
            return true;
        case '*':
            push(operands, pop(operands) * tempValue);//
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

int postfixCalculator(void *rawPostfixExpression) {
    Queue *postfixExpression = postfixExpressionParser(rawPostfixExpression);
    Stack *operands = createStack(); // it is going to keep numbers in the int form, not in ascii
    bool nextNumberParsing = true;
    while(!isQueueEmpty(postfixExpression)) {
        char token = dequeue(postfixExpression); 
        if ((token >= '(' && token <= '9') || token == ' ') { //
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
                    puts("Calculation error. ERR 10");
                    deleteStack(operands);
                    deleteQueue(postfixExpression);//
                    return 0;
                }
            }
        }
    }
    if (isStackEmpty(operands)) {
        puts("Calculation error. 11");
        deleteStack(operands);
        deleteQueue(postfixExpression);//
        return 0;
    }
    int resultValue = pop(operands);
    if (!isStackEmpty(operands)) {
        puts("Calculation error. 12");
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
    return postfixCalculator(sortingMachine(infixExpression));
}