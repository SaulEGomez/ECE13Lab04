// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"
#include "stack.c"

int main()
{
    BOARD_Init();

    printf("\n###### Saegomez's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    struct Stack stack;
    double poppedValue;
    int result;
    int testsFailed = 0;
    int testCases = 0;

    // Testing StackInit
    printf("Testing StackInit...\n");
    StackInit(&stack);
    testCases++;
    if (stack.currentItemIndex == -1 && stack.initialized) {
        printf("  StackInit, Proper Initialization: Success!\n");
    } else {
        printf("  StackInit, Proper Initialization: Failed!\n");
        testsFailed++;
    }

    // Ensuring the stack is marked as initialized
    testCases++;
    if (stack.initialized) {
        printf("  StackInit, Flag Set: Success!\n");
    } else {
        printf("  StackInit, Flag Set: Failed!\n");
        testsFailed++;
    }

    // Testing StackPush
    printf("Testing StackPush...\n");
    double testValue1 = 5.5;
    result = StackPush(&stack, testValue1);
    testCases++;
    if (result == SUCCESS && stack.stackItems[stack.currentItemIndex] == testValue1) {
        printf("  StackPush, Normal Operation: Success!\n");
    } else {
        printf("  StackPush, Normal Operation: Failed!\n");
        testsFailed++;
    }

    // Testing StackPush for stack overflow
    for (int i = 1; i < STACK_SIZE; i++) {
        StackPush(&stack, i);
    }
    testCases++;
    result = StackPush(&stack, 10.5);
    if (result == STANDARD_ERROR) {
        printf("  StackPush, Overflow: Success!\n");
    } else {
        printf("  StackPush, Overflow: Failed!\n");
        testsFailed++;
    }

    // Testing StackPop
    printf("Testing StackPop...\n");
    StackPop(&stack, &poppedValue);
    testCases++;
    if (poppedValue == 10.5 && stack.currentItemIndex == STACK_SIZE - 2) {
        printf("  StackPop, Normal Operation: Success!\n");
    } else {
        printf("  StackPop, Normal Operation: Failed!\n");
        testsFailed++;
    }

    // Testing StackPop for underflow
    stack.currentItemIndex = -1; // Reset stack to empty
    result = StackPop(&stack, &poppedValue);
    testCases++;
    if (result == STANDARD_ERROR) {
        printf("  StackPop, Underflow: Success!\n");
    } else {
        printf("  StackPop, Underflow: Failed!\n");
        testsFailed++;
    }

    // Testing StackIsEmpty
    printf("Testing StackIsEmpty...\n");
    StackInit(&stack); // Reinitializign to make sure it's empty
    result = StackIsEmpty(&stack);
    testCases++;
    if (result) {
        printf("  StackIsEmpty, Is Empty: Success!\n");
    } else {
        printf("  StackIsEmpty, Is Empty: Failed!\n");
        testsFailed++;
    }

    // Filling the stack and testing again
    StackPush(&stack, 1.0);
    result = StackIsEmpty(&stack);
    testCases++;
    if (!result) {
        printf("  StackIsEmpty, Not Empty: Success!\n");
    } else {
        printf("  StackIsEmpty, Not Empty: Failed!\n");
        testsFailed++;
    }

    // Testing StackIsFull
    printf("Testing StackIsFull...\n");
    // Emptying the stack and fill it to check for full condition
    StackInit(&stack);
    for (int i = 0; i < STACK_SIZE; i++) {
        StackPush(&stack, i);
    }
    result = StackIsFull(&stack);
    testCases++;
    if (result) {
        printf("  StackIsFull, Is Full: Success!\n");
    } else {
        printf("  StackIsFull, Is Full: Failed!\n");
        testsFailed++;
    }

    // Not full condition
    StackPop(&stack, &poppedValue); // Pop one item
    result = StackIsFull(&stack);
    testCases++;
    if (!result) {
        printf("  StackIsFull, Not Full: Success!\n");
    } else {
        printf("  StackIsFull, Not Full: Failed!\n");
        testsFailed++;
    }

    // Testing StackGetSize
    printf("Testing StackGetSize...\n");
    StackInit(&stack);
    StackPush(&stack, 1.0);
    StackPush(&stack, 2.0);
    int size = StackGetSize(&stack);
    testCases++;
    if (size == 2) {
        printf("  StackGetSize, Correct Size: Success!\n");
    } else {
        printf("  StackGetSize, Correct Size: Failed!\n");
        testsFailed++;
    }

    // Stack should report 0 when empty
    StackInit(&stack); // Reinitialize to empty
    size = StackGetSize(&stack);
    testCases++;
    if (size == 0) {
        printf("  StackGetSize, Zero Size: Success!\n");
    } else {
        printf("  StackGetSize, Zero Size: Failed!\n");
        testsFailed++;
    }

    printf("\nFinished testing. %d tests failed out of %d.\n", testsFailed, testCases);
    BOARD_End();
    return 0;
}


