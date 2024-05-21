// Saul Gomez ECE 13 stack.c 05.02.24
#include "rpn.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BOARD.h"

int ProcessBackspaces(char *rpn_sentence) {
    int read = 0, write = 0;
    while (rpn_sentence[read] != '\0') {
        if (rpn_sentence[read] == '\b') { 
            if (write > 0) { 
                write--;
            }
        } else {
            rpn_sentence[write++] = rpn_sentence[read];
        }
        read++;
    }
    rpn_sentence[write] = '\0'; 
    return write; 
}

int RPN_Evaluate(char *rpn_string, double *result) {
    char *token;
    struct Stack s;
    StackInit(&s);
    double op1, op2;

    ProcessBackspaces(rpn_string);

    token = strtok(rpn_string, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) { 
            double num = atof(token);
            if (StackIsFull(&s)) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
            StackPush(&s, num);
        } else { 
            if (StackPop(&s, &op2) != SUCCESS || StackPop(&s, &op1) != SUCCESS) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            switch (token[0]) {
                case '+':
                    *result = op1 + op2;
                    break;
                case '-':
                    *result = op1 - op2;
                    break;
                case '*':
                    *result = op1 * op2;
                    break;
                case '/':
                    if (op2 == 0) {
                        return RPN_ERROR_DIVIDE_BY_ZERO;
                    }
                    *result = op1 / op2;
                    break;
                default:
                    return RPN_ERROR_INVALID_TOKEN;
            }
            StackPush(&s, *result);
        }
        token = strtok(NULL, " ");
    }

    if (StackGetSize(&s) != 1) {
        return (StackGetSize(&s) == 0) ? RPN_ERROR_TOO_FEW_ITEMS_REMAIN : RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }

    StackPop(&s, result); 
    return RPN_NO_ERROR; 
}

