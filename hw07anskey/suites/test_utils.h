
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *hw7_suite(void);
extern Suite *my_string_suite(void);

#define tcase_hack(suite, setup_fixture, teardown_fixture, func)        \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** hw7 Header Info *********************************/
/******************************************************************************/

#define UNUSED_PARAM(x) ((void)x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void)x)  // This macro is only used for turning off compiler errors initially

// Success and failure codes for function return
#define SUCCESS 1
#define FAILURE 0

// Sizes for different arrays
#define MAX_ANIMAL_SIZE  64
#define MAX_SPECIES_LENGTH   10
#define MAX_HABITAT_LENGTH  10

// animal struct
struct animal {
    char    species[MAX_SPECIES_LENGTH];
    int     id;
    double  hungerScale;
    char    habitat[MAX_HABITAT_LENGTH];
};

extern struct animal animals[MAX_ANIMAL_SIZE];
extern int size;

// Prototype hw7.c functions
int addAnimal(const char *, int, double, const char *);
int updateAnimalSpecies(struct animal, const char *);
int swapAnimals(int, int);
int removeAnimal(struct animal);
double averageHungerScale(const char *);
int compareHabitat(struct animal, struct animal);
void sortAnimalsByHabitat(void);

// Function prototypes for my_string.c
size_t my_strlen(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strncpy(char *dest, const char *src, size_t n);

