/**
 * @file hw7.c
 * @author Nakul Kuttua
 * @collaborators Jungwoo Jang, Grace Wang
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2022-03-27
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
int addAnimal(const char *species, int id, double hungerScale, const char *habitat) {

  if (my_strlen(species) == 0 || my_strlen(habitat) == 0 || size >= MAX_ANIMAL_LENGTH) {
    return FAILURE;
  }

  if (my_strlen(species) >= MAX_SPECIES_LENGTH) {
    my_strncpy(animals[size].species, species, MAX_SPECIES_LENGTH - 1);
    animals[size].species[MAX_SPECIES_LENGTH - 1] = '\0';
  } else {
    my_strncpy(animals[size].species, species, my_strlen(species) + 1);
  }

  if (my_strlen(habitat) >= MAX_HABITAT_LENGTH) {
    my_strncpy(animals[size].habitat, habitat, MAX_HABITAT_LENGTH - 1);
    animals[size].habitat[MAX_HABITAT_LENGTH - 1] = '\0';
  } else {
    my_strncpy(animals[size].habitat, habitat, my_strlen(habitat) + 1);
  }

  animals[size].id = id;
  animals[size].hungerScale = hungerScale;
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
int updateAnimalSpecies(struct animal animal, const char *species) {
  
  int i = 0;

  while (i < size) {
    if (animals[i].id == animal.id) {

      if (my_strlen(species) >= MAX_SPECIES_LENGTH) {
        my_strncpy(animals[i].species, species, MAX_SPECIES_LENGTH - 1);
        animals[i].species[MAX_SPECIES_LENGTH - 1] = '\0';
      } else {
        my_strncpy(animals[i].species, species, my_strlen(species) + 1);
      }
      return SUCCESS;
    }

    i++;

  }

  return FAILURE;
}

/** averageHungerScale
* @brief Search for all animals with the same species and average the hungerScales
* 
* @param "species" Species that you want to find the average hungerScale for
* @return the average hungerScale of the specified species
*         if the species does not exist, return 0.0
*/
double averageHungerScale(const char *species) {
  
  double hungerTotal = 0;  // the variable to hold all the species' hungerScales added together
  int quantity = 0;        // the variable to hold all the species's recorded
  int i = 0;               // the iterate variable
  while (i < size) {
    if (my_strncmp(animals[i].species, species, my_strlen(species)) == 0) { // compare the current animal's species with the given parameter
      hungerTotal += animals[i].hungerScale;  // add the curent animal's hungerScale to the totalHunger
      quantity++;                             // increment the quantity because we found an animal
    }
    i++;                                      // increment i to iterate to the next animal
  }
  if (quantity == 0) {                        // if no animals were found, return 0.0 (double)
    return 0.0;                               
  } else {                                    // else, return hungerTotal / quantity as a double data type
    return (double) (hungerTotal / quantity);
  }
  
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
int swapAnimals(int index1, int index2) {
  if (index1 < 0 || index2 < 0 || index1 >= size || index2 >= size) {
      return FAILURE;
  }

  char speciesTemp[MAX_SPECIES_LENGTH];
  int idTemp = animals[index1].id;
  double hungerScaleTemp = animals[index1].hungerScale;
  char habitatTemp[MAX_HABITAT_LENGTH];

  my_strncpy(speciesTemp, animals[index1].species, my_strlen(animals[index1].species) + 1);
  my_strncpy(animals[index1].species, animals[index2].species, my_strlen(animals[index2].species) + 1);
  my_strncpy(animals[index2].species, speciesTemp, my_strlen(speciesTemp) + 1);

  animals[index1].id = animals[index2].id;
  animals[index2].id = idTemp;

  animals[index1].hungerScale = animals[index2].hungerScale;
  animals[index2].hungerScale = hungerScaleTemp;

  my_strncpy(habitatTemp, animals[index1].habitat, my_strlen(animals[index1].habitat) + 1);
  my_strncpy(animals[index1].habitat, animals[index2].habitat, my_strlen(animals[index2].habitat) + 1);
  my_strncpy(animals[index2].habitat, habitatTemp, my_strlen(habitatTemp) + 1);


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
int compareHabitat(struct animal animal1, struct animal animal2) {
  /*
  if (my_strncmp(animal1.habitat, animal2.habitat, MAX_HABITAT_LENGTH) < 0) {
    return -1;
  } else if (my_strncmp(animal1.habitat, animal2.habitat, MAX_HABITAT_LENGTH) > 0) {
    return 1;
  } else {
    return 0;
  }
  */
 return my_strncmp(animal1.habitat, animal2.habitat, MAX_HABITAT_LENGTH);
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
  int i; // iterate variable
  
  for (i = 0; i < size; i++) {
    if (animals[i].id == animal.id) { // check to see if the current animal's id is the same as the given animal id
        for (int j = i; j < size; j++) { 
          swapAnimals(j, j+1);        // keep swapping the desired animal until the animals on its right have all been shifted left 1 time
        }
        size--;  // decrement size because one animal has been removed
        return SUCCESS; // we have removed the animal so return SUCCESS
    }
  }

  return FAILURE; // only execute this line if no animals were removed
}

/** sortAnimal
 *
 * @brief using the compareHabitat function, sort the Animals in the array of
 * Animal structs, "animals," by the animals' habitat
 * If two animals have the same habitat, place the hungrier animal first
 *
 * @param void
 * @return void
 */
void sortAnimalsByHabitat(void) {

  int i, j;

   for (i = 0; i < size; i++) {
    int temp = i;
     for (j = i; j < size; j++) {
        if (compareHabitat(animals[j], animals[temp]) < 0) {
          temp = j;
        } else if (compareHabitat(animals[j], animals[temp]) == 0) {
          if (animals[temp].hungerScale < animals[j].hungerScale) {
            temp = j;
          }
        }
     }
     swapAnimals(i, temp);
   }
}
