#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"
#define PASSED_EXPRESSION_IS_INCORRECT 20

int priorityOfOperator(char thisOpeartor) {
    if (thisOpeartor == '+' || thisOpeartor == '-') {
        return 0;
    } else if (thisOpeartor == '/' || thisOpeartor == '*') {
        return 1;
    }
    return -1;
}

Queue *sortingMachine(char *infixExpession, int *errorCode) {
    Queue *postfixExpression = createQueue();
    Stack *operators = createStack();
    bool isExpressionCorrect = true;
    int infixExpressionLength = strlen(infixExpession);
    for (int i = 0; i < infixExpressionLength; ++i) {
        char token = infixExpession[i];
        if (token >= '0' && token <= '9') {
            enqueue(postfixExpression, token);
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            enqueue(postfixExpression, ' ');
            while (!isStackEmpty(operators) && priorityOfOperator(peekStack(operators)) >= priorityOfOperator(token)) {
                enqueue(postfixExpression, pop(operators));
                enqueue(postfixExpression, ' ');
            }
            push(operators, token);
        } else if (token == '(') {
            push(operators, token);
        } else if (token == ')') {
            while (!isStackEmpty(operators) && peekStack(operators) != '(') {
                enqueue(postfixExpression, ' ');
                enqueue(postfixExpression, pop(operators));
            }
            if (isStackEmpty(operators)) {
                isExpressionCorrect = false;
            } else {
                pop(operators);
            }
        }
    }

    while (!isStackEmpty(operators)) {
        if (peekStack(operators) == '(') {
            isExpressionCorrect = false;
        }
        enqueue(postfixExpression, ' ');
        enqueue(postfixExpression, pop(operators));
    }
    deleteStack(operators);
    
    if (!isExpressionCorrect) {
        *errorCode = PASSED_EXPRESSION_IS_INCORRECT;
        deleteQueue(postfixExpression);
        postfixExpression = createQueue();
    }
    return postfixExpression;
}

char *postfixExpressionToString(Queue *postfixExpression) {
    char *string = malloc(1024); 
    int stringLength = 0;
    while(!isQueueEmpty(postfixExpression)) {
        string[stringLength] = (char)dequeue(postfixExpression);
        ++stringLength;
    }
    string[stringLength] = '\0';
    deleteQueue(postfixExpression);
    return string;
}