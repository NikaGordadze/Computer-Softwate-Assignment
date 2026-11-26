#include <stdio.h>
#include <stdlib.h>
#include "orderedIntSet.h"

/* Patrick Barry (25403842) - menu options 7, 8 and 9.*/

#define MAX_SETS 10 /**< number of sets in SetsArray (delete if someone already defined it) */

/** Pointer to one of the set operations (setIntersection, setUnion, setDifference). */
typedef OrderedIntSet *(*SetOperation)(OrderedIntSet *, OrderedIntSet *);

/**
 * @brief Checks that an index is in the range 0 to MAX_SETS - 1.
 * @param index the index to check
 * @return 1 if valid, 0 otherwise
 */
static int validIndex(int index)
{
    return index >= 0 && index < MAX_SETS;
}

/**
 * @brief Shared code for menu options 7, 8 and 9.
 *
 * Reads three indices i1, i2, i3 from the input file, applies the
 * operation to the sets at i1 and i2, stores the result at i3
 * (deleting whatever set was there before) and prints the result.
 *
 * @param setsArray the array of set pointers
 * @param input     file the indices are read from
 * @param operation set function to apply
 * @param name      name of the operation, used in messages
 */
static void setOperationOption(OrderedIntSet *setsArray[], FILE *input,
                               SetOperation operation, const char *name)
{
    int i1;
    int i2;
    int i3;
    OrderedIntSet *result;

    if (fscanf(input, "%d %d %d", &i1, &i2, &i3) != 3)
    {
        printf("%s: could not read three indices\n\n", name);
        return;
    }

    if (!validIndex(i1) || !validIndex(i2) || !validIndex(i3))
    {
        printf("%s: indices must be in range 0-%d\n\n", name, MAX_SETS - 1);
        return;
    }

    if (setsArray[i1] == NULL || setsArray[i2] == NULL)
    {
        printf("%s: set %d or set %d does not exist\n\n", name, i1, i2);
        return;
    }

    /* compute first, so i3 may safely be the same as i1 or i2 */
    result = operation(setsArray[i1], setsArray[i2]);
    if (result == NULL)
    {
        printf("%s: ALLOCATION_ERROR\n\n", name);
        return;
    }

    /* free any set already stored at i3 so no memory is leaked */
    if (setsArray[i3] != NULL)
    {
        deleteOrderedSet(setsArray[i3]);
    }
    setsArray[i3] = result;

    printf("%s of set %d and set %d stored at index %d: ", name, i1, i2, i3);
    printToStdout(setsArray[i3]);
    printf("\n");
}

/**
 * @brief Menu option 7: intersection of sets i1 and i2, stored at i3.
 * @param setsArray the array of set pointers
 * @param input     file the indices are read from
 */
void intersectionOption(OrderedIntSet *setsArray[], FILE *input)
{
    setOperationOption(setsArray, input, setIntersection, "Intersection");
}

/**
 * @brief Menu option 8: union of sets i1 and i2, stored at i3.
 * @param setsArray the array of set pointers
 * @param input     file the indices are read from
 */
void unionOption(OrderedIntSet *setsArray[], FILE *input)
{
    setOperationOption(setsArray, input, setUnion, "Union");
}

/**
 * @brief Menu option 9: difference i1 - i2, stored at i3.
 * @param setsArray the array of set pointers
 * @param input     file the indices are read from
 */
void differenceOption(OrderedIntSet *setsArray[], FILE *input)
{
    setOperationOption(setsArray, input, setDifference, "Difference");
}

/**
 * @brief Reads a set index (0-9) from the input file.
 *
 * Does not check that a set exists at the index; callers must check
 * for NULL in SetsArray themselves.
 *
 * @param in Open input file (textInput.txt)
 * @return Index 0-9, or -1 if reading failed or the value is out of range
 */
int readIndex(FILE *in)
{
    int index;

    /* Fails on end of file or non-numeric input */
    if (fscanf(in, "%d", &index) != 1)
    {
        return -1;
    }

    /* Only indices 0-9 are valid for SetsArray */
    if (index < 0 || index >= MAX_SETS)
    {
        return -1;
    }

    return index;
}
/**
 * @brief Create an order set.
 *
 * Creates a new set and stores it in the
 * selected array position.
 * @param SetsArray Array of ordered sets.
 */
void createSetOption(OrderedIntSet *SetsArray[],FILE *inputFile ){
    //read index from file
    int index;
    fscanf(inputFile,"%d",&index);

    //delete old set if it exists
    if (SetsArray[index]!=NULL){
        deleteOrderedSet(SetsArray[index]);
    }

    //create new set
    SetsArray[index]=createOrderedSet();
    //print success message
    printf("Set %d created.\n", index);
}

/**
 * @brief Deletes an ordered set.
 *
 * Removes a set from the array and frees its memory.
 * @param SetsArray Array of ordered sets.
 */
void deleteSetOption(OrderedIntSet *SetsArray[],FILE *inputFile){
    //read index from file
    int index;
    fscanf(inputFile,"%d",&index);
    //delete set if it exists
    if (SetsArray[index]!=NULL){
        deleteOrderedSet(SetsArray[index]);
    }
    //remove pointer
    SetsArray[index]=NULL;
}