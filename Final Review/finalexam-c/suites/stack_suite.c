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

/* create_stack tests */
START_TEST(test_create_stack_normal) {
    struct my_stack *s = create_stack();
    ck_assert_msg(s != NULL, "create_stack() should not return NULL in normal case");
    struct mallocinfo *sinfo = _get_malloc_info(s);
    ck_assert_msg(sinfo->size == sizeof(struct my_stack), "create_stack() should allocate sizeof(struct my_stack) bytes for s (expected %lu bytes, got %lu bytes)", sizeof(struct my_stack), sinfo->size);
    ck_assert_msg(s->elements != NULL, "create_stack() should not set elements array to NULL");
    struct mallocinfo *elementsinfo = _get_malloc_info(s->elements);
    ck_assert_msg(elementsinfo->size == sizeof(int), "create_stack() should allocate space for 1 element for the elements array (expected %lu bytes, got %lu bytes)", sizeof(int), elementsinfo->size);
    ck_assert_msg(s->capacity == 1, "create_stack() should initialize capacity to 1 (got %d)", s->capacity);
    ck_assert_msg(s->numElements == 0, "create_stack() should initialize numElements to 0 (got %d)", s->numElements);

    struct my_stack *s2 = create_stack();
    ck_assert_msg(s != s2, "multiple calls to create_stack() should return different stack pointers");

    free(s->elements);
    free(s);
    free(s2->elements);
    free(s2);
}
END_TEST

START_TEST(test_create_stack_malloc_failure) {
    mallocs_until_fail = 0;
    struct my_stack *s = create_stack();
    ck_assert_msg(s == NULL, "create_stack() should return NULL on malloc failure");

    mallocs_until_fail = 1;
    s = create_stack();
    ck_assert_msg(s == NULL, "create_stack() should return NULL on malloc failure");
}
END_TEST

/* stack_push tests */

START_TEST(test_stack_push_NULL) {
    struct my_stack s = { .elements = NULL, .capacity = 1, .numElements = 0 };
    ck_assert_msg(stack_push(NULL, 42) == FAILURE, "stack_push() should return FAILURE if stack is NULL");
    ck_assert_msg(stack_push(&s, 42) == FAILURE, "stack_push() should return FAILURE if stack contains NULL element array");
}
END_TEST

START_TEST(test_stack_push_normal) {
    struct my_stack *s = _create_stack_with_data(5, 5, 1, 7, -3, 84); // [5, 1, 7], capacity = 5
    s->numElements -= 2; // make sure there is room for the new element

    int ret = stack_push(s, 42);
    ck_assert_msg(ret == SUCCESS, "stack_push() should return SUCCESS if push succeeds");
    ck_assert_msg(s->numElements == 4, "stack_push() should increase numElements by 1 (expected 4, got %d)", s->numElements);
    ck_assert_msg(s->elements[3] == 42, "stack_push() should add the new element to the end of the array (expected 42, got %d)", s->elements[3]);

    free(s->elements);
    free(s);
}
END_TEST

START_TEST(test_stack_push_resize) {
    struct my_stack *s = _create_stack_with_data(4, 5, 1, 7, 3); // [5, 1, 7, 3], capacity = 4

    int ret = stack_push(s, 42);
    ck_assert_msg(ret == SUCCESS, "stack_push() should return SUCCESS if push succeeds");
    ck_assert_msg(s->numElements == 5, "stack_push() should increase numElements by 1 (expected 5, got %d)", s->numElements);
    ck_assert_msg(s->elements != NULL, "stack_push() should not set elements array to NULL");
    struct mallocinfo *info = _get_malloc_info(s->elements);
    ck_assert_msg(s->elements[4] == 42, "stack_push() should add the new element to the end of the array (expected 42, got %d)", s->elements[4]);
    ck_assert_msg(s->capacity == 8, "stack_push() should double capacity (expected 8, got %d)", s->capacity);
    ck_assert_msg(info->size == 8 * sizeof(int), "stack_push() should double the backing array size (expected %lu bytes, got %lu bytes)", 8 * sizeof(int), info->size);

    free(s->elements);
    free(s);

    s = _create_stack_with_data(6, 1, -5, 73, 2, -55, 6); // [1, -5, 73, 2, -55, 6], capacity = 6
    ret = stack_push(s, 85);
    ck_assert_msg(ret == SUCCESS, "stack_push() should return SUCCESS if push succeeds");
    ck_assert_msg(s->numElements == 7, "stack_push() should increase numElements by 1 (expected 7, got %d)", s->numElements);
    ck_assert_msg(s->elements != NULL, "stack_push() should not set elements array to NULL");
    info = _get_malloc_info(s->elements);
    ck_assert_msg(s->elements[6] == 85, "stack_push() should add the new element to the end of the array (expected 85, got %d)", s->elements[6]);
    ck_assert_msg(s->capacity == 12, "stack_push() should double capacity (expected 12, got %d)", s->capacity);
    ck_assert_msg(info->size == 12 * sizeof(int), "stack_push() should double the backing array size (expected %lu bytes, got %lu bytes)", 12 * sizeof(int), info->size);

    free(s->elements);
    free(s);
}
END_TEST

START_TEST(test_stack_push_malloc_failure) {
    struct my_stack *s = _create_stack_with_data(5, 1, 2, 3, 4, 5); // [1, 2, 3, 4, 5], capacity = 5
    struct my_stack *s2 = _create_stack_with_data(4, -1, 33, 27, -5); // [-1, 33, 27, -5], capacity = 4

    mallocs_until_fail = 0;
    int ret = stack_push(s, 8192);
    ck_assert_msg(ret == FAILURE, "stack_push() should return FAILURE on malloc failure");
    ret = stack_push(s2, 73);
    ck_assert_msg(ret == FAILURE, "stack_push() should return FAILURE on malloc failure");
}
END_TEST

/* stack_pop tests */
START_TEST(test_stack_pop_NULL) {
    struct my_stack s = { .elements = NULL, .capacity = 1, .numElements = 0 };
    struct my_stack *s2 = _create_stack();
    int dataOut;
    ck_assert_msg(stack_pop(NULL, &dataOut) == FAILURE, "stack_pop() should return FAILURE if stack is NULL");
    ck_assert_msg(stack_pop(&s, &dataOut) == FAILURE, "stack_pop() should return FAILURE if stack contains NULL element array");
    ck_assert_msg(stack_pop(s2, NULL) == FAILURE, "stack_pop() should return FAILURE if dataOut is NULL");
    ck_assert_msg(stack_pop(NULL, NULL) == FAILURE, "stack_pop() should return FAILURE if stack and dataOut are NULL");

    free(s2->elements);
    free(s2);
}
END_TEST

START_TEST(test_stack_pop_empty) {
    struct my_stack *s = _create_stack();
    int dataOut;
    ck_assert_msg(stack_pop(s, &dataOut) == FAILURE, "stack_pop() should return FAILURE if stack is empty");
}
END_TEST

START_TEST(test_stack_pop_normal) {
    struct my_stack *s = _create_stack_with_data(4, 1, 8, -23, -5); // [1, 8, -23, -5], capacity = 4
    int dataOut = 0xDEADBEEF;
    ck_assert_msg(stack_pop(s, &dataOut) == SUCCESS, "stack_pop() should return SUCCESS if push succeeds");
    ck_assert_msg(s->numElements == 3, "stack_pop() should decrease numElements by 1 (expected 3, got %d)", s->numElements);
    ck_assert_msg(s->elements != NULL, "stack_pop() should not set elements array to NULL");
    struct mallocinfo *info = _get_malloc_info(s->elements);
    ck_assert_msg(dataOut != (int) 0xDEADBEEF, "stack_pop() should modify dataOut");
    ck_assert_msg(dataOut == -5, "stack_pop() should set dataOut to the last element in the array (expected -5, got %d)", dataOut);
    ck_assert_msg(s->capacity == 4, "stack_pop() should not change capacity");
    ck_assert_msg(info->size == 4 * sizeof(int), "stack_pop() should not change backing array size");

    free(s->elements);
    free(s);
}
END_TEST

START_TEST(test_stack_pop_not_full) {
    struct my_stack *s = _create_stack_with_data(8, 1, 2, 3, 4, 5, 6, 7, 8); // [1, 2, 3, 4, 5], capacity = 8
    s->numElements -= 3;
    int dataOut = 0xDEADBEEF;
    ck_assert_msg(stack_pop(s, &dataOut) == SUCCESS, "stack_pop() should return SUCCESS if push succeeds");
    ck_assert_msg(s->numElements == 4, "stack_pop() should decrease numElements by 1 (expected 4, got %d)", s->numElements);
    ck_assert_msg(s->elements != NULL, "stack_push() should not set elements array to NULL");
    struct mallocinfo *info = _get_malloc_info(s->elements);
    ck_assert_msg(dataOut != (int) 0xDEADBEEF, "stack_pop() should modify dataOut");
    ck_assert_msg(dataOut == 5, "stack_pop() should set dataOut to the last element in the array (expected 5, got %d)", dataOut);
    ck_assert_msg(s->capacity == 8, "stack_pop() should not change capacity");
    ck_assert_msg(info->size == 8 * sizeof(int), "stack_pop() should not change backing array size");

    free(s->elements);
    free(s);
}
END_TEST

Suite *stack_suite(void)
{
    Suite *s = suite_create("stack_suite");

    // create_stack tests
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_create_stack_normal);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_create_stack_malloc_failure);

    // stack_push tests
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_push_NULL);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_push_normal);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_push_resize);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_push_malloc_failure);

    // stack_pop tests
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_pop_NULL);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_pop_empty);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_pop_normal);
    tcase_singleton(s, reset_mallocs_until_fail_and_malloclist, free_malloclist, test_stack_pop_not_full);

    return s;
}
