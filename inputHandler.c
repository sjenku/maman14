#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers/inputHandler.h"
#include "headers/tools.h"

void runRulessOnLinesOfFile(int argc, char *argv[], int numOfRules, int (*rulesArr[])(char *))
{
    int i, j;
    char *filename;
    FILE *f;
    size_t size = MAX_CHARS_INLINE;
    char *line = (char *)malloc(size);

    /*Iterate threw each file*/
    for (i = 1; i < argc; i++)
    {
        logger(I, "The Iteretion %d out of %d", i, argc - 1);
        filename = argv[i];
        f = fopen(filename, "r");
        if (f != NULL)
        {
            logger(L, "File is reading");
            logger(I, "The File Name is => %s", filename);
            /*handle each line in the file*/
            /* while (fgets(line, size, f) != NULL) */
            while (getline(&line, &size, f) != -1)
            {
                line[strlen(line) - 1] = '\0'; /*Set the last char to null character instead of the newline char*/
                logger(I, "the line is => %s", line);
                for (j = 0; j < numOfRules; j++)
                    rulesArr[j](line);
            }
            fclose(f);
        }
    }
    free(line);
}

/* void printBinaryRepresentation()
// {
//     int a[10], n, i;
//     printf("Enter the number to convert: ");
//     scanf("%d", &n);
//     for (i = 0; n > 0; i++)
//     {
//         a[i] = n % 2;
//         n = n / 2;
//     }
//     printf("\nBinary of Given Number is=");
//     for (i = i - 1; i >= 0; i--)
//     {
//         printf("%d", a[i]);
//     }
//     printf("\n");
// }
*/
