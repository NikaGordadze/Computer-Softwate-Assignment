/**
 * @file menu.c
 * @brief Menu options for creating, editing, storing and combining ordered sets.
 */

#include <stdio.h>
#include <stdlib.h>
#include "orderedIntSet.h"
#include "menu.h"

/* Patrick Barry (25403842) - menu options 7, 8 and 9.*/

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
 * @param lowerName lowercase name of the operation, used in prompts
 */
static void setOperationOption(OrderedIntSet *setsArray[], FILE *input,
                               SetOperation operation, const char *name,
                                const char *lowerName)
{
    int i1;
    int i2;
    int i3;
    OrderedIntSet *result;

    printf("Please enter three indices: two for sets to form %s of and one for the target set:\n", lowerName);
    if (fscanf(input, "%d %d %d", &i1, &i2, &i3) != 3)
    {
        printf("%s: could not read three indices\n", name);
        return;
    }

    if (!validIndex(i1) || !validIndex(i2) || !validIndex(i3))
    {
        printf("%s: indices must be in range 0-%d\n", name, MAX_SETS - 1);
        return;
    }

    if (setsArray[i1] == NULL || setsArray[i2] == NULL)
    {
        if (setsArray[i1] == NULL)
        {
            printf("No ordered set available at index %d. ", i1);
        }
        if (setsArray[i2] == NULL)
        {
            printf("No ordered set available at index %d. ", i2);
        }
        printf("Cannot perform set %s.\n", lowerName);
        return;
    }

    /* compute first, so i3 may safely be the same as i1 or i2 */
    result = operation(setsArray[i1], setsArray[i2]);
    if (result == NULL)
    {
        printf("%s: ALLOCATION_ERROR\n", name);
        return;
    }

    /* free any set already stored at i3 so no memory is leaked */
    if (setsArray[i3] != NULL)
    {
        deleteOrderedSet(setsArray[i3]);
    }
    setsArray[i3] = result;

    printf("Set %s = ", name);
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
    setOperationOption(setsArray, input, setIntersection, "Intersection", "intersection");
}

/**
 * @brief Menu option 8: union of sets i1 and i2, stored at i3.
 * @param setsArray the array of set pointers
 * @param input     file the indices are read from
 */
void unionOption(OrderedIntSet *setsArray[], FILE *input)
{
    setOperationOption(setsArray, input, setUnion, "Union", "union");
}

/**
 * @brief Menu option 9: difference i1 - i2, stored at i3.
 * @param setsArray the array of set pointers
 * @param input     file the indices are read from
 */
void differenceOption(OrderedIntSet *setsArray[], FILE *input)
{
    setOperationOption(setsArray, input, setDifference, "Difference", "difference");
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
    printf("Please enter index (0 - 9) for set to be created:\n");
    index = readIndex(inputFile);
    //returns -1 if index is not valid
    if (index == -1) {
        printf("Invalid index\n");
        return;
    }

    //delete old set if it exists
    if (SetsArray[index]!=NULL){
        deleteOrderedSet(SetsArray[index]);
    }

    //create new set
    SetsArray[index]=createOrderedSet();
    //print success message
    printf("Set at index %d created\n", index);
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
    printf("Please enter index (0 - 9) for set to be deleted:\n");
    index = readIndex(inputFile);
    //returns -1 if index is not valid
    if (index == -1) {
        printf("Invalid index\n");
        return;
    }
    //delete set if it exists
    if (SetsArray[index]!=NULL){
        deleteOrderedSet(SetsArray[index]);
    }
    //remove pointer
    SetsArray[index]=NULL;
    //print success message
    printf("Set at index %d deleted\n", index);
}

/* Denys Denysov (25461192) - initSetsArray, addElementsOption, removeElementsOption, storeSetsOption, loadSetsOption */

/** Name of the binary file used to store/load the SetsArray. */
#define SETS_FILE_NAME "SetsArrayFile.bin"

/**
 * @brief initSetsArray
 * Sets all entries of the sets array to NULL.
 * @param setsArray array of MAX_SETS pointers to ordered sets
 */
void initSetsArray(OrderedIntSet *setsArray[])
{
    int i;

    for (i = 0; i < MAX_SETS; i++)
    {
        setsArray[i] = NULL;
    }
}

/**
 * @brief addElementsOption (menu 3)
 * Add elements to an ordered set.
 *
 * Reads the set index, then reads numbers until a negative number is read.
 * Each number is added with addElement() and the result is reported.
 * The set is printed.
 *
 * @param in input file (textInput.txt)
 * @param setsArray array of MAX_SETS pointers to ordered sets
 */
void addElementsOption(FILE *in, OrderedIntSet *setsArray[])
{
    int index;
    int number;

    printf("Please enter index (0 - 9) for set to add elements to:\n");
    if (fscanf(in, "%d", &index) != 1)
    {
        printf("Could not read set index.\n");
        return;
    }
    if (index < 0 || index >= MAX_SETS || setsArray[index] == NULL)
    {
        printf("Invalid index or set %d does not exist.\n", index);
        return;
    }

    printf("Please enter element (enter value <0 to stop): ");
    while (fscanf(in, "%d", &number) == 1 && number >= 0)
    {
        switch (addElement(setsArray[index], number))
        {
        case NUMBER_ADDED:
            printf("Result: SOK\n");
            break;
        case NUMBER_ALREADY_IN_SET:
            printf("Result: NUMBER_ALREADY_IN_SET\n");
            break;
        case ALLOCATION_ERROR:
            printf("Result: ALLOCATION_ERROR\n");
            break;
        default:
            break;
        }
        printf("Please enter element (enter value <0 to stop): ");
    }

    printf("Final ordered set = ");
    printToStdout(setsArray[index]);
    printf("\n");
}

/**
 * @brief removeElementsOption (menu 4)
 * Removes elements from an ordered set.
 *
 * Reads the set index, then reads numbers until a negative number is read.
 * Each number is removed with removeElement() and the result is reported.
 * The set is printed.
 *
 * @param in input file (textInput.txt)
 * @param setsArray array of MAX_SETS pointers to ordered sets
 */
void removeElementsOption(FILE *in, OrderedIntSet *setsArray[])
{
    int index;
    int number;

    printf("Please enter index (0 - 9) for set to remove elements from:\n");
    if (fscanf(in, "%d", &index) != 1)
    {
        printf("Could not read set index.\n");
        return;
    }
    if (index < 0 || index >= MAX_SETS || setsArray[index] == NULL)
    {
        printf("Invalid index or set %d does not exist.\n", index);
        return;
    }

    printf("Please enter element (enter value <0 to stop): ");
    while (fscanf(in, "%d", &number) == 1 && number >= 0)
    {
        switch (removeElement(setsArray[index], number))
        {
        case NUMBER_REMOVED:
            printf("Result: SOK\n");
            break;
        case NUMBER_NOT_IN_SET:
            printf("Result: NUMBER_NOT_IN_SET\n");
            break;
        case ALLOCATION_ERROR:
            printf("Result: ALLOCATION_ERROR\n");
            break;
        default:
            break;
        }
        printf("Please enter element (enter value <0 to stop): ");
    }

    printf("Final ordered set = ");
    printToStdout(setsArray[index]);
    printf("\n");
}

/**
 * @brief storeSetsOption (menu 5)
 * Stores the entire SetsArray in "SetsArrayFile.bin".
 *
 * File format: for each of the MAX_SETS entries an int flag (0 = no set,
 * 1 = set present). If the flag is 1, an int with the number of elements
 * follows, followed by the elements (ints) in ascending order.
 *
 * @param setsArray array of MAX_SETS pointers to ordered sets
 */
void storeSetsOption(OrderedIntSet *setsArray[])
{
    FILE *file;
    int i;
    int k;
    int present;
    int count;
    int value;

    file = fopen(SETS_FILE_NAME, "wb");
    if (file == NULL)
    {
        printf("Could not open %s for writing.\n", SETS_FILE_NAME);
        return;
    }

    for (i = 0; i < MAX_SETS; i++)
    {
        present = (setsArray[i] != NULL);
        if (fwrite(&present, sizeof(int), 1, file) != 1)
        {
            printf("Write to %s failed.\n", SETS_FILE_NAME);
            fclose(file);
            return;
        }
        if (!present)
        {
            continue;
        }

        count = setsArray[i]->count;
        if (fwrite(&count, sizeof(int), 1, file) != 1)
        {
            printf("Write to %s failed.\n", SETS_FILE_NAME);
            fclose(file);
            return;
        }

        gotoHead(setsArray[i]->list);
        for (k = 0; k < count; k++)
        {
            gotoNextNode(setsArray[i]->list);
            value = getData(setsArray[i]->list);
            if (fwrite(&value, sizeof(int), 1, file) != 1)
            {
                printf("Write to %s failed.\n", SETS_FILE_NAME);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("All sets saved to file\n");
}

/**
 * @brief loadSetsOption (menu 6)
 * Loads the entire SetsArray from "SetsArrayFile.bin".
 *
 * The file is first read into a temporary array. Only if the whole file was
 * read successfully, the old sets are deleted and replaced by the loaded ones.
 *
 * @param setsArray array of MAX_SETS pointers to ordered sets
 */
void loadSetsOption(OrderedIntSet *setsArray[])
{
    FILE *file;
    OrderedIntSet *loaded[MAX_SETS];
    int i;
    int k;
    int present;
    int count;
    int value;
    int ok = 1;
    int numSets = 0;

    file = fopen(SETS_FILE_NAME, "rb");
    if (file == NULL)
    {
        printf("Could not open %s for reading.\n", SETS_FILE_NAME);
        return;
    }

    initSetsArray(loaded);

    for (i = 0; i < MAX_SETS && ok; i++)
    {
        if (fread(&present, sizeof(int), 1, file) != 1)
        {
            ok = 0;
            break;
        }
        if (!present)
        {
            continue;
        }

        if (fread(&count, sizeof(int), 1, file) != 1 || count < 0)
        {
            ok = 0;
            break;
        }

        numSets++;
        loaded[i] = createOrderedSet();
        if (loaded[i] == NULL)
        {
            ok = 0;
            break;
        }

        for (k = 0; k < count; k++)
        {
            if (fread(&value, sizeof(int), 1, file) != 1 ||
                addElement(loaded[i], value) == ALLOCATION_ERROR)
            {
                ok = 0;
                break;
            }
        }
    }

    fclose(file);

    if (!ok)
    {
        printf("Loading from %s failed, sets unchanged.\n", SETS_FILE_NAME);
        for (i = 0; i < MAX_SETS; i++)
        {
            if (loaded[i] != NULL)
            {
                deleteOrderedSet(loaded[i]);
            }
        }
        return;
    }

    /* success: replace old sets by loaded ones */
    for (i = 0; i < MAX_SETS; i++)
    {
        if (setsArray[i] != NULL)
        {
            deleteOrderedSet(setsArray[i]);
        }
        setsArray[i] = loaded[i];
    }

    printf("expect %d number of sets\n", numSets);
    printf("Loaded %d number of sets\n", numSets);
}