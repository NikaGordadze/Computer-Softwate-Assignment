#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include "orderedIntSet.h"
/**
 * @brief Create a set in the array.
 *
 * Creates a new ordered set and stores it in the
 * selected position.
 * @param SetsArray Array of set pointers.
 */
void createSetOption(OrderedIntSet*SetsArray[],FILE *inputFile);
/**
 * @brief Deletes a set from array.
 *
 * Removes the set from the selected position in the array.
 * @param SetsArray Array of set pointers.
 */
void deleteSetOption(OrderedIntSet*SetsArray[],FILE *inputFile);

#define MAX_SETS 10 /**< number of sets in SetsArray */

void intersectionOption(OrderedIntSet *setsArray[], FILE *input);
void unionOption(OrderedIntSet *setsArray[], FILE *input);
void differenceOption(OrderedIntSet *setsArray[], FILE *input);
int readIndex(FILE *in);
void initSetsArray(OrderedIntSet *setsArray[]);
void addElementsOption(FILE *in, OrderedIntSet *setsArray[]);
void removeElementsOption(FILE *in, OrderedIntSet *setsArray[]);
void storeSetsOption(OrderedIntSet *setsArray[]);
void loadSetsOption(OrderedIntSet *setsArray[]);
#endif // MENU_H