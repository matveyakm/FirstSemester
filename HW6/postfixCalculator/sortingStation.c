#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"

bool isPriorityOfThisOperatorIsBigger(int thisOperator, int anotherOperator) {
    return (thisOperator == '*' || thisOperator == "/") > (anotherOperator == '*' || anotherOperator == "/");
}

Queue *sortingMachine(char *infixExpession) {
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
            while (!isStackEmpty(operators) && isPriorityOfThisOperatorIsBigger(peekStack(operators), token)) {
                enqueue(postfixExpression, ' ');
                enqueue(postfixExpression, pop(operators));
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
        puts("Passed expression is not correct!");
        deleteQueue(postfixExpression);
        postfixExpression = createQueue();
    }
    return postfixExpression;
}

char *postfixExpressionToString(Queue *postfixExpression) {
    char *string = malloc(0); //
    int stringLength = 0;
    while(!isQueueEmpty(postfixExpression)) {
        string[stringLength] = (char)dequeue(postfixExpression);
        ++stringLength;
    }
    deleteQueue(postfixExpression);
    return string;
}