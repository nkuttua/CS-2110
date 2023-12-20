/**
 * @file my_string.c
 * @author Nakul Kuttua
 * @collaborators Jungwoo Jang, Grace Wang
 * @brief Your implementation of these famous 3 string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2022-03-27
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
size_t my_strlen(const char *s) {
  
  int count = 0; // count the amount of letters
  int i = 0;     // iterate variable
  char c = *(s + i);   // go to the memory address of i and get the value

  while (c != '\0') {
    count++;          // because the current char is not the null term, it has to be a letter and so count++
    i++;              // increment i so we can access the next letter
    c = *(s + i);     // get the next char
  }

  return count;       // return the amount of letters in the string s
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
int my_strncmp(const char *s1, const char *s2, size_t n) {

  size_t i = 0;           // iterator variable
  
  while (i < n) {        // loop
    char a = *(s1 + i);  // get the char at index i for a
    char b = *(s2 + i);  // get the char at index i for b
    if (a < b) {         // compare
      return -1;      
    } else if (a > b) {  // compare
      return 1;
    }
    i++;                 // increment
  }

  return 0;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n) {

  size_t i = 0;              // increment variable

  while (i < n) {
    char a = *(src + i);     // get the char at index i for src
    if (a != '\0') {         // check to see if the char is not the null term
      *(dest + i) = a;       // if it is not, then the dest receives the curr char
    } else {
      *(dest + i) = '\0';    // otherwise, the dest receives the null term
      break;                 // immediately break
    }
    i++;                     // increment
  }

  if (i < n) {               // if the inc is less than n
    while (i < my_strlen(src)) {
      *(dest + i) = '\0';
      i++;
    }
  }

  char *temp = dest;
  return temp;
}
