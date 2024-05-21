// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int evalResult;

    printf("Welcome to Saegomez's RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and operators (+ - * /) in RPN format:\n");

        if (fgets(rpn_sentence, sizeof(rpn_sentence), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        // Checking if input length exceeds 60 characters (excluding newline and null terminator)
        if (strlen(rpn_sentence) > MAX_INPUT_LENGTH) {
            printf("Input exceeds maximum length of 60 characters.\n");
            continue;
        }

        // Removing any trailing newline character
        if (rpn_sentence[strlen(rpn_sentence) - 1] == '\n') {
            rpn_sentence[strlen(rpn_sentence) - 1] = '\0';
        }

        evalResult = RPN_Evaluate(rpn_sentence, &result);

        // Handling the result and possible errors
        switch (evalResult) {
            case RPN_NO_ERROR:
                printf("Result = %f\n", result);
                break;
            case RPN_ERROR_STACK_OVERFLOW:
                printf("Error: Stack overflow.\n");
                break;
            case RPN_ERROR_STACK_UNDERFLOW:
                printf("Error: Stack underflow.\n");
                break;
            case RPN_ERROR_INVALID_TOKEN:
                printf("Error: Invalid token encountered.\n");
                break;
            case RPN_ERROR_DIVIDE_BY_ZERO:
                printf("Error: Division by zero.\n");
                break;
            case RPN_ERROR_TOO_FEW_ITEMS_REMAIN:
                printf("Error: Too few items remain after evaluation.\n");
                break;
            case RPN_ERROR_TOO_MANY_ITEMS_REMAIN:
                printf("Error: Too many items remain after evaluation.\n");
                break;
            default:
                printf("An unknown error occurred.\n");
        }
    }

    return 0;  
}