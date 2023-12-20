/**
 * CS 2110 - Fall 2021
 * Final Exam - Implement Stack
 *
 * Do not modify this file!
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

#define FAILURE 1
#define SUCCESS 0

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED(x) ((void)(x))

struct my_stack {
    int *elements;   // pointer to the element at index 0 of the stack
    int numElements; // the number of elements currently in the stack
    int capacity;    // the current allocated size of the elements array
};

struct my_stack *create_stack(void);
int stack_push(struct my_stack *stack, int data);
int stack_pop(struct my_stack *stack, int *dataOut);

#endif
