
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *tl4_suite(void);

// Define a check containing only one test case of the same name
#define tcase_singleton(suite, setup_fixture, teardown_fixture, func)   \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** tl4 Header Info *********************************/
/******************************************************************************/

#define DEBUG_FLAG "-d"

#include "../tl04.h"

extern const char *names[7];

extern int _queue_add(struct student_t);
extern int _queue_remove(struct student_t *);

extern struct student_t _create_temp_student(const char *name, enum assignment_t assignment);
extern void _delete_queue(void);
extern int _name_was_deepcopied(const char *name);
extern void _free_student_name_safe(struct student_t *student);
