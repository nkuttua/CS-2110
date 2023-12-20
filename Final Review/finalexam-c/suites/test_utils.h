
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100
#include "mallocinfo.h"

// Suites
extern Suite *stack_suite(void);

// Define a check containing only one test case of the same name
#define tcase_singleton(suite, setup_fixture, teardown_fixture, func)   \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

#define DEBUG_FLAG "-d"

#include "../stack.h"

// TODO: function declarations below

struct my_stack *_create_stack(void);
struct my_stack *_stack_push(struct my_stack*, int);
struct my_stack *_create_stack_with_data(int, ...);
int _num_malloc_calls(void);
struct mallocinfo *_get_malloc_info(void*);