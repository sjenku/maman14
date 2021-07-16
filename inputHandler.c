#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "headers/inputHandler.h"
#include "headers/tools.h"

int isCommentLine(char *line)
{
    /*Temperory char holder of each char in the line*/
    char *ch;
    /*Iterate threw the line*/
    for (ch = line; *ch != '\0'; ch++)
    {
        if (!isspace(*ch))
            /*Checking if the ';' char in the begining
         of the line that indecates that is a comment*/
            if (*ch == ';')
            {
                logger(I, "Is comment Line =>%s\n", line);
                return SUCCESS;
            }
    }
    return FAILURE;
}

int isOperationLine(const char *line)
{
}

void readPrintLineFile(int argc, char *argv[])
{
    size_t size = 10;
    char *string = (char *)malloc(size);
    for (int i = 1; i < argc; i++)
    {
        logger(I, "The Iteretion %d out of %d\n", i, argc);
        char *filename = argv[i];
        FILE *f = fopen(filename, "r");
        if (f != NULL)
        {
            int bytes_read;
            logger(L, "File is reading\n");
            logger(I, "The File Name is => %s\n", filename);
            for (int j = 1; (bytes_read = getline(&string, &size, f)) != -1; j++)
            {
                //write to file
                logger(I, "%s", string);
                isCommentLine(string);
            }
            fclose(f);
        }
    }
    free(string);
}

// void printBinaryRepresentation()
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