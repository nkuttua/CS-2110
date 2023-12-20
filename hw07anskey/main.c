/**
 * @file main.c
 * @author YOUR NAME HERE
 * @brief testing and debugging functions written in my_string.c and hw7.c
 * @date 2021-03-xx
 */

// You may add and remove includes as necessary to help facilitate your testing
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

/** main
 *
 * @brief used for testing and debugging functions written in my_string.c and hw7.c
 *
 * @param void
 * @return 0 on success
 */
int main(void)
{
    printf("Hello, I will be printed when you run %s and %s!\n", "make hw7", "./hw7");

    // Let's test my_string.c
    const char *s = "I'm a string literal";
    int s_len = my_strlen(s); // just implicitly convert size_t to int so I can use %d
    printf("Len is %d\n", s_len);

    // testing hw7.c
    printf("size %d\n", size); // size is defined as extern in hw7.h
    const char *species = "Student";
    int id = 66;
    double hungerScale = 1.5;
    const char *habitat = "Clough";
    int success = addAnimal(species, id, hungerScale, habitat);
    // I could put this below line in a for loop to print every single animal
    printf("success adding? %d, new size: %d, species: %s, id: %d, hunger: %f, habitat: %s\n", success, size, animals[0].species, animals[0].id, animals[0].hungerScale, animals[0].habitat);
}
