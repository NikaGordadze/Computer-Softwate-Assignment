/**
 * @file menu.h
 * @brief Declarations for the menu options of the ordered set test program.
 */

#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include "orderedIntSet.h"

void createSetOption(OrderedIntSet*SetsArray[],FILE *inputFile);
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