    /**
 * CS 2110 - Fall 2021
 * Final Exam - Implement Stack
 * 
 * Name: Neil Kochhar
 */

/**
 * The following my_stack struct is defined in stack.h. You will need to use this to store your stack's data:
 * 
 * struct my_stack {
 *   int *elements;   // pointer to the element at index 0 of the stack
 *   int numElements; // the number of elements currently in the stack
 *   int capacity;    // the current allocated size of the elements array
 * };
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include "stack.h"

/** create_stack
 *
 * Dynamically allocate and initialize a my_stack struct that contains elements (an array of int elements
 * representing the stack), numElements (the number of elements currently in the stack), and 
 * capacity (the maximum number of elements that can currently be stored in the elements array).
 * 
 * The bottom of the stack should be at index 0 and the top of the stack should be at the highest index.
 * 
 * You must do the following:
 * 1. Your my_stack struct's element array must be dynamically allocated.
 * 2. Your array should be initialized with enough space to store exactly one element.
 * 3. All member variables of your struct should be initialized to correct values.
 * 
 * If dynamic memory allocation fails at any point, you should immediately free the stack struct and any dynamically 
 * allocated members of the struct and return NULL.
 *
 * @return returns NULL if memory allocation fails, returns a pointer to your stack otherwise.
 */
struct my_stack *create_stack(void)
{
    struct my_stack *mystack = malloc(sizeof(struct my_stack));
    if (mystack == NULL) {
        return NULL;
    }

    mystack->elements = malloc(sizeof(int));
    if (mystack->elements == NULL) {
        free(mystack);
        return NULL;
    }
    mystack->numElements = 0;
    mystack->capacity = 1;
    return mystack;
}

/** stack_push
 *
 * Pushes the value data onto the top of the stack. If your stack does not have enough space to push another 
 * element, you must double the size of your dynamically allocated array. 
 * 
 * If dynamic memory allocation fails at any point, you should immediately free the stack struct and any dynamically 
 * allocated members of the struct and return FAILURE.
 * 
 * @param stack A pointer to the stack struct.
 * @param data The value to be pushed onto the stack.
 * @return FAILURE if the stack or its element array is NULL or memory allocation fails, otherwise SUCCESS.
 */
int stack_push(struct my_stack *stack, int data)
{
    if (stack == NULL || stack->elements == NULL) {
        return FAILURE;
    }

    if ((stack->numElements + 1) > stack->capacity) {
        stack = realloc(stack, (stack->capacity*2));
        if (stack == NULL) {
            free(stack);
            return FAILURE;
        }
        stack->capacity = stack->capacity * 2;

    }
    stack->elements[stack->numElements] = data;
    stack->numElements++;


    return SUCCESS;
}

/** stack_pop
 *
 * Pops off the top element of the stack, AND stores the popped element's data into dataOut. You should 
 * not decrease the size of the allocated memory for the elements array.
 * 
 * If the stack is empty or dynamic memory allocation fails at any point, you should immediately free the
 * stack struct and any dynamically allocated members of the struct and return NULL.
 * 
 * @param stack A pointer to the stack struct.
 * @param dataOut A pointer to the variable where you should store the popped element's data.
 * @return FAILURE if the stack or its element array or dataOut is NULL or a remove is attempted from an empty stack, otherwise SUCCESS.
 */
int stack_pop(struct my_stack *stack, int *dataOut)
{
    if (stack == NULL || stack->elements == NULL || dataOut == NULL) {
        return FAILURE;
    }

    if (stack->numElements == 0) {
        free(stack->elements);
        free(stack);
        return FAILURE;
    }

    *dataOut = stack->elements[stack->numElements - 1];
    
    stack->numElements--;
    
    return SUCCESS;


}
