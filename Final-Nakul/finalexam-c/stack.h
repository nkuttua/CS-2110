/**
 * CS 2110 - Spring 2022
 * Final Exam - Implement Stack
 *
 * Do not modify this file!
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FAILURE 1
#define SUCCESS 0

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED(x) ((void)(x))

struct my_stack {
    struct data_t *elements;   // pointer to the element at index 0 of the stack
    int numElements; // the number of elements currently in the stack
    int capacity;    // the current allocated size of the elements array
};

struct data_t {
    int length; // length of the string this array element points to
    char *data; // the string itself, allocated on the heap
};

int push(struct my_stack *stack, char *data);

#endif
