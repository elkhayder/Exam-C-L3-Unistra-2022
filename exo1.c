#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "constants.h"

int main(int argc, char **argv)
{
    /* Lettre à compter */
    char l = 's';
    /* Nombre d'occurence */
    unsigned int Occ = 0;
    /* Current read Character */
    char c;
    /* Max distance between the two chars */
    unsigned int D = 0;
    /* Holds distances count */
    unsigned int *data;
    /* Max distance reoccurence */
    unsigned int max_dist = 0;
    /* Vars for loops */
    unsigned int i, y;

    /* Open file */
    FILE *file = fopen(LOREM_IPSUM_FILENAME, "r");
    /* Verify if file has been open, exit otherwise */
    if (file == NULL)
    {
        fprintf(stderr, ERR_READ_FILE, LOREM_IPSUM_FILENAME);
        exit(EXIT_FAILURE);
    }

    /* Make sure we are in the top on the file */
    rewind(file);

    do
    {
        /* Read char */
        c = fgetc(file);

        if (tolower(c) == l)
        {
            Occ++;
        }

        /** End loop on end of file*/
    } while (c != EOF);

    /* Print char occ */
    printf(MSG_OCCURENCES_COUNT, l, Occ, LOREM_IPSUM_FILENAME);

    /* Rewind file cursor */
    rewind(file);

    /**
     * Keep reading until encoutring the first char in l to start counting
     */
    do
    {
        c = fgetc(file);
    } while (tolower(c) != l && c != EOF);

    /* Chars in between buffer */
    unsigned int charsCount = 0;

    while (c != EOF)
    {
        if (tolower(c) == l)
        {
            /* Select the greater count*/
            if (charsCount > D)
            {
                D = charsCount;
            }
            /* Reset count */
            charsCount = 0;
        }
        else
        {
            /* Increment count*/
            charsCount++;
        }

        /* Read next char */
        c = fgetc(file);
    }

    /* No need to have this as defined const since it's language independant */
    printf(MSG_MAX_DISTANCE, l, D);

    /**
     * An unsigned int where the value is 0 in binary is 0
     * Starting with a memory set to 0s is the same as setting each unsigned int to 0
     */
    /* // TODO: Should it be D or D + 1 ? */
    data = calloc(D + 1, sizeof(unsigned int));

    /* Exit if allocation fails */
    if (data == NULL)
    {
        fprintf(stderr, ERR_MEM_ALLOC);
        exit(EXIT_FAILURE);
    }

    /* Rewind file cursor */
    rewind(file);

    /**
     * Keep reading until encoutring the first char in l to start counting
     */
    do
    {
        c = fgetc(file);
    } while (tolower(c) != l && c != EOF);

    /* Reset chars count buffer */
    charsCount = 0;

    while (c != EOF)
    {
        if (tolower(c) == l)
        {
            /* Increment this occurence */
            data[charsCount]++;
            charsCount = 0;
        }
        else
        {
            charsCount++;
        }

        /* Get next char */
        c = fgetc(file);
    }

    for (i = 0; i < D + 1; i++)
    {
        if (data[i] > max_dist)
        {
            max_dist = data[i];
        }
    }

    /* Print table */
    for (i = 0; i < D + 1; i++)
    {
        printf("%4u : ", i);

        for (y = 0; y < (data[i] * 40 / max_dist); y++)
        {
            printf("*");
        }

        printf("\n");
    }

    /* Cleanup */
    free(data);
    fclose(file);

    return EXIT_SUCCESS;
}