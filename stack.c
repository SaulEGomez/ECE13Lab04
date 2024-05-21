// Saul Gomez ECE 13 stack.c 05.02.24
#include "stack.h"
#include "BOARD.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define EMPTY_INDEX -1

void StackInit(struct Stack *stack) {
    stack->currentItemIndex = EMPTY_INDEX;
    stack->initialized = TRUE; 
}

int StackPush(struct Stack *stack, double value) {
    if (!stack->initialized || StackIsFull(stack)) {
        return STANDARD_ERROR;
    }
    stack->currentItemIndex++;
    stack->stackItems[stack->currentItemIndex] = value;
    return SUCCESS; 
}

int StackPop(struct Stack *stack, double *value) {
    if (!stack->initialized || StackIsEmpty(stack)) {
        return STANDARD_ERROR;
    }
    *value = stack->stackItems[stack->currentItemIndex];
    stack->currentItemIndex--;
    return SUCCESS;
}

int StackIsEmpty(const struct Stack *stack) {
    return stack->initialized && stack->currentItemIndex == EMPTY_INDEX;
}

int StackIsFull(const struct Stack *stack) {
    return stack->initialized && stack->currentItemIndex == STACK_SIZE - 1;
}

int StackGetSize(const struct Stack *stack) {
    if (!stack->initialized) {
        return SIZE_ERROR; 
    }
    return stack->currentItemIndex + 1;
}


