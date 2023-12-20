// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global macros, structures and fields to be used by the
 * hw7 program.
 */
#ifndef HW7_H
#define HW7_H

#include <stddef.h>

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially

// Success and failure codes for function return
#define SUCCESS 1
#define FAILURE 0

// Sizes for different arrays
#define MAX_SPECIES_LENGTH  10
#define MAX_HABITAT_LENGTH  10
#define MAX_ANIMAL_LENGTH   64

// animal struct
struct animal {
    char    species[MAX_SPECIES_LENGTH];
    int     id;
    double  hungerScale;
    char    habitat[MAX_HABITAT_LENGTH];
};
extern struct animal animals[];
extern int size;
// Prototype hw7.c functions
int addAnimal(const char *, int, double, const char *);
int removeAnimal(struct animal);
int updateAnimalSpecies(struct animal, const char *);
double averageHungerScale(const char *);
int swapAnimals(int, int);
int compareHabitat(struct animal, struct animal);
void sortAnimalsByHabitat(void);

#endif