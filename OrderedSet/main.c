#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/** name of the input file with the menu commands */
#define INPUT_FILE_NAME "textInput.txt"

/**
 * @brief Reads menu choices from textInput.txt and executes them.
 * @return EXIT_SUCCESS on normal termination, EXIT_FAILURE if the input file cannot be opened
 */
int main(void)
{
    OrderedIntSet *setsArray[MAX_SETS];
    FILE *in;
    int choice;
    int i;

    in = fopen(INPUT_FILE_NAME, "r");
    if (in == NULL)
    {
        printf("Could not open %s.\n", INPUT_FILE_NAME);
        return EXIT_FAILURE;
    }

    initSetsArray(setsArray);

    while (fscanf(in, "%d", &choice) == 1 && choice != 10)
    {
        switch (choice)
        {
        case 1:
            createSetOption(setsArray, in);
            break;
        case 2:
            deleteSetOption(setsArray, in);
            break;
        case 3:
            addElementsOption(in, setsArray);
            break;
        case 4:
            removeElementsOption(in, setsArray);
            break;
        case 5:
            storeSetsOption(setsArray);
            break;
        case 6:
            loadSetsOption(setsArray);
            break;
        case 7:
            intersectionOption(setsArray, in);
            break;
        case 8:
            unionOption(setsArray, in);
            break;
        case 9:
            differenceOption(setsArray, in);
            break;
        default:
            printf("Invalid menu choice: %d\n", choice);
            break;
        }
        printf("\n"); /* blank line after each menu choice */
    }

    /* free all remaining sets */
    for (i = 0; i < MAX_SETS; i++)
    {
        if (setsArray[i] != NULL)
        {
            deleteOrderedSet(setsArray[i]);
            setsArray[i] = NULL;
        }
    }

    fclose(in);
    return EXIT_SUCCESS;
}