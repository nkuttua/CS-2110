/**
 * CS 2110 - Fall 2021
 * Final Exam - Implement Stack
 *
 * You may use this file to test your functions from stack.c
 */

#include "stack.h"

/**
 * @brief A main function that you can use for testing.
 * 
 * Implementing this function is NOT necessary for the final.
 * You can use this if you want to create custom tests.
 * We have included a basic test as an example.
 * 
 */
int main(void) {
    struct my_stack *stack = create_stack();
    printf("Stack capacity: %d\n", stack->capacity);
    printf("Stack numElements: %d\n", stack->numElements);
    
    stack_push(stack, 1);
    printf("Stack capacity: %d\n", stack->capacity);
    printf("Stack numElements: %d\n", stack->numElements);
    printf("Inside our return stack after pushing 1:\n");
    for (int i = 0; i < stack->numElements; i++) {
        printf("%d ", stack->elements[i]);
    }
    printf("\n");

    int dataOut = -1;
    stack_pop(stack, &dataOut);
    printf("Stack capacity: %d\n", stack->capacity);
    printf("Stack numElements: %d\n", stack->numElements);
    printf("dataOut after popping: %d\n", dataOut);
    printf("Inside our return stack after popping:\n");
    for (int i = 0; i < stack->numElements; i++) {
        printf("%d ", stack->elements[i]);
    }
    printf("\n");

    return 0;
}
