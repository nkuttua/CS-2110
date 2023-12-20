/**
 * @file stack_suite.c
 * @author Sameer
 * @brief Testing Suites to Final-C - Fall 2021
 * @date 2021-12-04
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

int mallocs_until_fail = -1;
struct mallocinfo *malloclist;

// allow infinite mallocs by default
static void reset_mallocs_until_fail_and_malloclist(void) {
    malloclist = NULL;
    mallocs_until_fail = -1;
}

static void free_malloclist(void) {
    struct mallocinfo *curr = malloclist;
    while (curr != NULL) {
        struct mallocinfo *next = curr->next;
        free(curr);
        curr = next;
    }
}


/* stack_push tests */

START_TEST(test_push_NULL) {
    // Stack with NULL elements for testing
    struct my_stack s = { .elements = NULL, .capacity = 10, .numElements = 0 };

    // The actual tests
    ck_assert_msg(push(NULL, "BCSE") == FAILURE, "push() should return FAILURE if stack is NULL");
    ck_assert_msg(_num_malloc_calls() == 0, "push() shouldn't call malloc if stack is NULL");
    ck_assert_msg(push(&s, "BCSE") == FAILURE, "push() should return FAILURE if stack contains NULL element array");
    ck_assert_msg(_num_malloc_calls() == 0, "push() shouldn't call malloc if stack contains NULL element array");
    ck_assert_msg(push(&s, NULL) == FAILURE, "push() should return FAILURE if the string passed in is NULL");
    ck_assert_msg(_num_malloc_calls() == 0, "push() shouldn't call malloc if the string passed in is NULL");
}
END_TEST

START_TEST(test_push_normal_retval) {
    // Create a dummy stack
    // It's okay if the elements here are on the stack. They'll never be freed
    struct data_t e0 = { .length = 4, .data = "BCSE" };
    struct data_t e1 = { .length = 6, .data = "CS2110" };
    struct data_t eb = { .length = 0, .data = NULL };
    struct data_t e[] = { e0, e1, eb };
    struct my_stack s = { .elements = e, .numElements = 2, .capacity = 3 };
    char *d = "test string";

    // The actual tests
    int ret = push(&s, d);
    ck_assert_msg(ret == SUCCESS, "push() should return SUCCESS if push succeeds");

    // Free for memory leaks
    free(s.elements[2].data);
}
END_TEST

START_TEST(test_push_normal_metadata) {
    // Create a dummy stack
    // It's okay if the elements here are on the stack. They'll never be freed
    struct data_t e0 = { .length = 4, .data = "BCSE" };
    struct data_t e1 = { .length = 6, .data = "CS2110" };
    struct data_t eb = { .length = 0, .data = NULL };
    struct data_t e[] = { e0, e1, eb };
    struct my_stack s = { .elements = e, .numElements = 2, .capacity = 3 };
    char *d = "test string";

    // The actual tests
    push(&s, d);
    ck_assert_msg(s.numElements == 3, "push() should increase numElements by 1 (expected 3, got %d)", s.numElements);
    ck_assert_msg(s.capacity == 3, "push() shouldn't increase the capacity if it isn't needed (expected 3, got %d)", s.capacity);
    ck_assert_msg(s.elements != NULL, "push() should not set elements array to NULL");

    // Free for memory leaks
    free(s.elements[2].data);
}
END_TEST

START_TEST(test_push_normal_data) {
    // Create a dummy stack
    // It's okay if the elements here are on the stack. They'll never be freed
    struct data_t e0 = { .length = 4, .data = "BCSE" };
    struct data_t e1 = { .length = 6, .data = "CS2110" };
    struct data_t eb = { .length = 0, .data = NULL };
    struct data_t e[] = { e0, e1, eb };
    struct my_stack s = { .elements = e, .numElements = 2, .capacity = 3 };
    char *d = "test string";

    // The actual tests
    push(&s, d);
    ck_assert_msg(s.elements[2].length == ((int) strlen(d)), "push() should set the length of the data (expected 11, got %d)", s.elements[2].length);
    ck_assert_msg(s.elements[2].data != d, "push() should deep copy the data");
    ck_assert_msg(strncmp(s.elements[2].data, d, strlen(d) + 1) == 0, "push() should copy the data correctly (expected \"test string\", got \"%s\")", s.elements[2].data);

    // Free for memory leaks
    free(s.elements[2].data);
}
END_TEST

START_TEST(test_push_capacity) {
    // Create a dummy stack
    // It's okay if the elements here are on the stack. They'll never be freed
    struct data_t e0 = { .length = 4, .data = "BCSE" };
    struct data_t e1 = { .length = 6, .data = "CS2110" };
    struct data_t e[] = { e0, e1 };
    struct my_stack s = { .elements = e, .numElements = 2, .capacity = 2 };
    char *d = "test string";

    // The actual tests
    int ret = push(&s, d);
    ck_assert_msg(ret == FAILURE, "push() should return FAILURE if there isn't enough space");
    ck_assert_msg(_num_malloc_calls() == 0, "push() shouldn't call malloc if there isn't enough space");
}
END_TEST

START_TEST(test_push_malloc_failure) {
    // Create a dummy stack
    // It's okay if the elements here are on the stack. They'll never be freed
    struct data_t e0 = { .length = 4, .data = "BCSE" };
    struct data_t e1 = { .length = 6, .data = "CS2110" };
    struct data_t eb = { .length = 0, .data = NULL };
    struct data_t e[] = { e0, e1, eb, eb };
    struct my_stack s = { .elements = e, .numElements = 2, .capacity = 4 };
    char *d = "test string";

    // The actual tests
    mallocs_until_fail = 0;
    int ret = push(&s, d);
    ck_assert_msg(ret == FAILURE, "push() should return FAILURE on malloc failure");
}
END_TEST

Suite *stack_suite(void)
{
    Suite *s = suite_create("stack_suite");

    // push tests
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_push_NULL);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_push_normal_retval);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_push_normal_metadata);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_push_normal_data);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_push_capacity);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_push_malloc_failure);

    return s;
}
