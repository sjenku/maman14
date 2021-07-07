#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void readPrintLineFile(int argc, char *argv[])
{
    char *numCopy = "1";
    size_t size = 10;
    char *string = (char *)malloc(size);
    for (int i = 1; i < argc; i++)
    {
        printf("The Iteretion %d out of %d\n", i, argc);
        char *filename = argv[i];
        FILE *f = fopen(filename, "r");
        char fCopyName[12];
        snprintf(fCopyName, 12, "copy%d.txt", i);
        printf("fcopy=> %s", fCopyName);
        FILE *fCopy = fopen(fCopyName, "w");
        if (f != NULL)
        {
            int bytes_read;
            printf("File is reading\n");
            printf("The File Name is => %s\n", filename);
            for (int j = 1; (bytes_read = getline(&string, &size, f)) != -1; j++)
            {
                //write to file
                printf("%s", string);
                fputs(string, fCopy);
            }
            fclose(f);
        }
        if (fCopy != NULL)
            fclose(fCopy);
        numCopy++;
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
    printf("number of argc => %d\n", argc);
    // readPrintLineFile(argc, argv);
    // printBinaryRepresentation();
    return 0;
}