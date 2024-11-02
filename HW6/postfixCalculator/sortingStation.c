#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"

bool isPriorityOfThisOperatorIsBigger(int thisOperator, int anotherOperator) {
    return (thisOperator == '*' || thisOperator == '/') > (anotherOperator == '*' || anotherOperator == '/');
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
        puts("Passed expression is not correct!");
        deleteQueue(postfixExpression);
        postfixExpression = createQueue();
    }
    return postfixExpression;
}

char *postfixExpressionToString(Queue *postfixExpression) {
    char *string = malloc(1024); // <-- изменение на вменяемое число приводит к ОЧЕНЬ странным симптомам
    // при 0 в какой-то момент, ожидаемо, заполнение залазит на защищенную память. но этого момента довольно стабильно работает
    // иногда в postfixCalculator подаётся пустая очередь. никакой логической связи с этим методом нет. но фактически, она есть
    //
    // при адекватно выделении памяти в out лезет считываемый файл из теста (не имею ни малейшего представления каким образом это связано и как вообще это технически возможно)
    int stringLength = 0;
    while(!isQueueEmpty(postfixExpression)) {
        string[stringLength] = (char)dequeue(postfixExpression);
        ++stringLength;
    }
    string[stringLength] = '\0';
    deleteQueue(postfixExpression);
    return string;
}