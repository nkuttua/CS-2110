/**
 * @file main.c
 * @brief testing and debugging functions written in tl04.c
 * @date 2022-04-xx
 */

// You may add and remove includes as necessary to help facilitate your testing
#include <stdio.h>
#include "tl04.h"

/** main
 *
 * @brief used for testing and debugging functions written in my_string.c and hw7.c
 *
 * @param void
 * @return 0 on success
 */
int main(void)
{
    printf("Hello, I will be printed when you run %s and %s!\n", "make tl04", "./tl04");

    // Let's test tl04.c
    printf("We can access queue_head and queue_tail as shown in this line, %d\n", queue_head == NULL && queue_tail == NULL);
    struct student_t student;
    student.name = NULL;
    int success = queue_add(student);
    printf("Success? %d\n", success);
}
