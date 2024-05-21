// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"
#include "rpn.c"

int main() {
    BOARD_Init();
    printf("\n###### Saegomez's rpn test harness ####\n\n");

    double result;
    int error;
    int testsFailed = 0;
    int testCases = 0;

    // Array of test cases for RPN_Evaluate
    struct {
        char *input;
        double expected;
        int expectedError;
    } rpnTests[] = {
        {"1 1 +", 2.0, RPN_NO_ERROR},
        {"1 2 -", -1.0, RPN_NO_ERROR},
        {"2 3 *", 6.0, RPN_NO_ERROR},
        {"4 2 /", 2.0, RPN_NO_ERROR},
        {"1 2 + 3 4 + *", 21.0, RPN_NO_ERROR},
        {"1 0 /", 0.0, RPN_ERROR_DIVIDE_BY_ZERO},
        {"1 +", 0.0, RPN_ERROR_STACK_UNDERFLOW},
        {"abc 10 20 +", 0.0, RPN_ERROR_INVALID_TOKEN},
        {"2 2 2 +", 0.0, RPN_ERROR_TOO_MANY_ITEMS_REMAIN},
        {"", 0.0, RPN_ERROR_TOO_FEW_ITEMS_REMAIN},
        {"-1 -1 +", -2.0, RPN_NO_ERROR},
        {"0.5 0.5 +", 1.0, RPN_NO_ERROR},
        {"3 5 8 * 7 + *", 141.0, RPN_NO_ERROR},  
        {"5 1 2 + 4 * 3 - +", 14.0, RPN_NO_ERROR},  
        {"9 6 - 1 5 - *", 15.0, RPN_NO_ERROR},  
        {"2.5 3.2 + 2 *", 11.4, RPN_NO_ERROR},  
        {"2 2 * 2 2 * +", 8.0, RPN_NO_ERROR},  
        {"10 2 8 * + 9 -", 25.0, RPN_NO_ERROR},  
        {"6 2 / 3 /", 1.0, RPN_NO_ERROR},  
        {"3 3 * 3 3 * 3 3 * + +", 36.0, RPN_NO_ERROR} 
    };

    for (int i = 0; i < sizeof(rpnTests) / sizeof(rpnTests[0]); i++) {
        testCases++;
        printf("Testing RPN_Evaluate with \"%s\"...\n", rpnTests[i].input);
        error = RPN_Evaluate(rpnTests[i].input, &result);
        if (error != rpnTests[i].expectedError || (error == RPN_NO_ERROR && result != rpnTests[i].expected)) {
            printf("   Failed, expected = %f, got = %f, expected error = %d, got error = %d\n",
                   rpnTests[i].expected, result, rpnTests[i].expectedError, error);
            testsFailed++;
        } else {
            printf("   Success!\n");
        }
    }

    // Test cases for ProcessBackspaces
    struct {
        char input[255];
        char expected[255];
    } pbTests[] = {
        {"123\b34", "1234"}, 
        {"abc\b\bde\b\b\b123", "123"},
        {"\b\b123\b\b", "1"},
        {"hello world\b\b\b\b\b\b\b\b\b\b\b\b\b123", "123"},
        {"test\b\b\b\btest\b\b\b\b", ""},
        {"\b\b\b", ""},
        {"12\b\b34\b\b56", "56"}
    };

    for (int i = 0; i < sizeof(pbTests) / sizeof(pbTests[0]); i++) {
        testCases++;
        ProcessBackspaces(pbTests[i].input);
        printf("Testing ProcessBackspaces with \"%s\"... should be \"%s\"\n", pbTests[i].input, pbTests[i].expected);
        if (strcmp(pbTests[i].input, pbTests[i].expected) != 0) {
            printf("   Failed, result = %s\n", pbTests[i].input);
            testsFailed++;
        } else {
            printf("   Success!\n");
        }
    }

    printf("\nFinished testing. %d tests failed out of %d.\n", testsFailed, testCases);
    BOARD_End();
    return 0;
}
