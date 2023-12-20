/**
 * @file my_string.c
 * @author YOUR NAME HERE
 * @brief Your implementation of these famous 3 string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2021-10-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"

/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
    const char *old = s;
    while (*s++);
    return s - old - 1;
}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    char x, y;
    int result = 0;
    // Professor Southern's very fun one-liner
    while (!(result = (x = *s1++) - (y = *s2++)) && (x || y) && n--);
    return result;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
    // Direct translation from the man page
    size_t i;

    for (i = 0; i < n && *(src + i); ++i) {
        *(dest + i) = *(src + i);
    }
    for (; i < n; i++) {
        *(dest + i) = '\0';
    }

    return dest;
}
