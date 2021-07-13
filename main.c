#include <stdlib.h>
#include <stdio.h>
#include "symbolList.h"

void readPrintLineFile(int argc, char *argv[])
{
    size_t size = 10;
    char *string = (char *)malloc(size);
    for (int i = 1; i < argc; i++)
    {
        printf("The Iteretion %d out of %d\n", i, argc);
        char *filename = argv[i];
        FILE *f = fopen(filename, "r");
        if (f != NULL)
        {
            int bytes_read;
            printf("File is reading\n");
            printf("The File Name is => %s\n", filename);
            for (int j = 1; (bytes_read = getline(&string, &size, f)) != -1; j++)
            {
                //write to file
                printf("%s", string);
            }
            fclose(f);
        }
    }
    free(string);
}

void printBinaryRepresentation()
{
    int a[10], n, i;
    printf("Enter the number to convert: ");
    scanf("%d", &n);
    for (i = 0; n > 0; i++)
    {
        a[i] = n % 2;
        n = n / 2;
    }
    printf("\nBinary of Given Number is=");
    for (i = i - 1; i >= 0; i--)
    {
        printf("%d", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    /*Create Symbols List*/
    symbolsList *symbols = (symbolsList *)malloc(sizeof(symbolsList)); //TODO:Free malloc

    addSymbol(symbols, "Jhon", 100);
    addSymbol(symbols, "Jessica", 104);
    addSymbol(symbols, "George", 112);

    printSymbolsFrom(symbols->head);

    return 0;
}