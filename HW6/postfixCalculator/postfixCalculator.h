#pragma once

// Note: it can calculate numbers only with 1 digit in its notation!
// Note: also it can parse only "+ - * /" operators and round brackets if it is in an infix form
// Note: You must pass numbers with the negative value (for exaple, A) in this way: "0 - B", where 'B' = abs(A)

int postfixCalculator(void *rawPostfixExpression);
// Pass a pointer to a string with expression in a postfix form or to a queue generated by sorting station

int calculator(char *infixExpression);