#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers/inputHandler.h"
#include "headers/tools.h"

void runRulessOnLinesOfFile(char *filename, void (*rulesFunc)(char *, int, char *))
{
    int lineNumber;
    FILE *f;
    size_t size = MAX_CHARS_INLINE;
    char *line = (char *)malloc(size);

    f = fopen(filename, "r");
    if (f != NULL)
    {
        /*handle each line in the file*/
        lineNumber = 1;
        while (getline(&line, &size, f) != -1)
        {
            line[strlen(line) - 1] = '\0'; /*Set the last char to null character instead of the newline char*/
                                           /*Implement rulaFunc on the each line*/
            rulesFunc(line, lineNumber, filename);
            lineNumber++;
        }
        fclose(f);
    }
    free(line);
}
