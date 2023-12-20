/**
 * @file hw7.c
 * @author SOLUTION FILE
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2022-03-xx
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

// Global array of Animal structs
struct animal animals[MAX_ANIMAL_LENGTH];

int size = 0;

/** addAnimal
 *
 * @brief creates a new Animal and adds it to the array of Animal structs, "animals"
 *
 *
 * @param "species" species of the animal being created and added
 *               NOTE: if the length of the species (including the null terminating character)
 *               is above MAX_SPECIES_LENGTH, truncate species to MAX_SPECIES_LENGTH. If the length
 *               is 0, return FAILURE.  
 *               
 * @param "id" id of the animal being created and added
 * @param "hungerScale" hunger scale of the animal being created and added
 * @param "habitat" habitat of the animal being created and added
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "species" length is 0
 *         (2) "habitat" length is 0
 *         (3) adding the new animal would cause the size of the array "animals" to
 *             exceed MAX_ANIMAL_LENGTH
 *        
 */
int addAnimal(const char *species, int id, double hungerScale, const char *habitat)
{
  //if not enough space in array, return failure
  if (size >= MAX_ANIMAL_LENGTH) {
    return FAILURE;
  }
  // check if species name is too short, if so return failure
  if (my_strlen(species) == 0) {
    return FAILURE;
  }

  // check if habitat name is too short, if so return failure
  if (my_strlen(habitat) == 0){
    return FAILURE;
  }

  // Check species, if it is too long, truncate it
  if (my_strlen(species) >= MAX_SPECIES_LENGTH) {
    my_strncpy(animals[size].species, species, MAX_SPECIES_LENGTH - 1);
    animals[size].species[MAX_SPECIES_LENGTH - 1] = 0;
  } else {
    my_strncpy(animals[size].species, species, my_strlen(species) + 1);
  }

  // Check habitat, if it is too long, truncate it
  if (my_strlen(habitat) >= MAX_HABITAT_LENGTH) {
    my_strncpy(animals[size].habitat, habitat, MAX_HABITAT_LENGTH - 1);
    animals[size].habitat[MAX_HABITAT_LENGTH - 1] = 0;
  } else {
    my_strncpy(animals[size].habitat, habitat, my_strlen(habitat) + 1);
  }

  // copy over id and hungerScale
  animals[size].id = id;
  animals[size].hungerScale = hungerScale;

  // add created Animal to animals, just increment size since its already in array
  size++;
  return SUCCESS;
}

/** updateAnimalSpecies
 *
 * @brief updates the species of an existing animal in the array of Animal structs, "animals"
 *
 * @param "animal" Animal struct that exists in the array "animals"
 * @param "species" new species of Animal "animal"
 *               NOTE: if the length of species (including the null terminating character)
 *               is above MAX_SPECIES_LENGTH, truncate species to MAX_SPECIES_LENGTH
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the Animal struct "animal" can not be found in the array "animals" based on its id
 */
int updateAnimalSpecies(struct animal animal, const char *species)
{
  // iterate through array and look for a Animal with the same id
  for (int i = 0; i < size; i++) {
    if (animals[i].id == animal.id) {
      // if same id found, update species
      if (my_strlen(species) + 1 >= MAX_SPECIES_LENGTH) {
        // truncate long names
        my_strncpy(animals[i].species, species, MAX_SPECIES_LENGTH - 1);
        animals[i].species[MAX_SPECIES_LENGTH - 1] = 0;
        return SUCCESS;
      } else {
        // update normal len species
        my_strncpy(animals[i].species, species, my_strlen(species) + 1);
        return SUCCESS;
      }
    }
  }

  // if same id not found, return failure
  return FAILURE;
}

/** averageHungerScale
* @brief Search for all animals with the same species and find average the hungerScales
* 
* @param "species" Species that you want to find the average hungerScale for
* @return the average hungerScale of the specified species
*         if the species does not exist, return 0.0
*/
double averageHungerScale(const char *species)
{
  double average = 0.0;
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (my_strncmp(animals[i].species, species, my_strlen(species) + 1) == 0) {
      average += animals[i].hungerScale;
      count++;
    }
  }
  if (count != 0) {
    return (average / count);
  } else {
    return 0.0;
  }
  return 0.0;
}

/** swapAnimals
 *
 * @brief swaps the position of two Animal structs in the array of Animal structs, "animals"
 *
 * @param "index1" index of the first Animal struct in the array "animals"
 * @param "index2" index of the second Animal struct in the array "animals"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "index1" and/or "index2" are negative numbers
 *         (2) "index1" and/or "index2" are out of bounds of the array "animals"
 */
int swapAnimals(int index1, int index2)
{
  // bounds checks
  if (index1 < 0 || index1 >= size) return FAILURE;
  if (index2 < 0 || index2 >= size) return FAILURE;

  // swap animal id
  int animalsID = animals[index1].id;
  animals[index1].id = animals[index2].id;
  animals[index2].id = animalsID;

  // swap hungerScale
  double hungerScales = animals[index1].hungerScale;
  animals[index1].hungerScale = animals[index2].hungerScale;
  animals[index2].hungerScale = hungerScales;

  // swap species
  char species[MAX_SPECIES_LENGTH];
  my_strncpy(species, animals[index1].species, my_strlen(animals[index1].species) + 1);
  my_strncpy(animals[index1].species, animals[index2].species, my_strlen(animals[index2].species) + 1);
  my_strncpy(animals[index2].species, species, my_strlen(species) + 1);

  // swap habitat
  char habitat[MAX_HABITAT_LENGTH];
  my_strncpy(habitat, animals[index1].habitat, my_strlen(animals[index1].habitat) + 1);
  my_strncpy(animals[index1].habitat, animals[index2].habitat, my_strlen(animals[index2].habitat) + 1);
  my_strncpy(animals[index2].habitat, habitat, my_strlen(habitat) + 1);

  return SUCCESS;
}

/** removeAnimal
 *
 * @brief removes Animal in the array of Animal structs, "animals", that has the same species
 *
 * @param "animal" Animal struct that exists in the array "animals"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the Animal struct "animal" can not be found in the array "animals"
 */
int removeAnimal(struct animal animal)
{
  // search for animal to remove
  int i;
  for (i = 0; i < size; i++) {
    if (animal.id == animals[i].id) {
      break;
    }
  }

  // if reached the end of the array, did not find Animal
  if (i == size) {
    return FAILURE;
  }

  // swap all the way down to remove the Animal
  for (int j = i; j < size; j++) {
    swapAnimals(j, j + 1);
  }

  size--;
  return SUCCESS;
}

/** compareHabitat
 *
 * @brief compares the two Animals animals' habitats (using ASCII)
 *
 * @param "animal1" Animal struct that exists in the array "animals"
 * @param "animal2" Animal struct that exists in the array "animals"
 * @return negative number if animal1 is less than animal2, positive number if animal1 is greater
 *         than animal2, and 0 if animal1 is equal to animal2
 */
int compareHabitat(struct animal animal1, struct animal animal2)
{
  
  // compare habitats
  int animal1Length = my_strlen(animal1.habitat) + 1;
  int animal2Length = my_strlen(animal2.habitat) + 1;
  int shortest = animal1Length < animal2Length ? animal1Length : animal2Length;

  return my_strncmp(animal1.habitat, animal2.habitat, shortest);

}

/** sortAnimal
 *
 * @brief using the compareHabitat function, sort the Animals in the array of
 * Animal structs, "animals," by the animals' habitat
 * If two animals have the same habitat, place the hungier animal first
 *
 * @param void
 * @return void
 */
void sortAnimalsByHabitat(void)
{
  int i, j, min_idx;
 
  // One by one move boundary of unsorted subarray
  for (i = 0; i < size-1; i++)
  {
    // Find the minimum element in unsorted array
    min_idx = i;
    for (j = i+1; j < size; j++) {
      if (compareHabitat(animals[j], animals[min_idx]) == 0) {
        if (animals[j].hungerScale - animals[min_idx].hungerScale > 0) {
          min_idx = j;
        }
      }
      else if (compareHabitat(animals[j], animals[min_idx]) < 0) {
        min_idx = j;
      }
    }

    // Swap the found minimum element with the first element
    swapAnimals(min_idx, i);
  }
}