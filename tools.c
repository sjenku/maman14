#include <stdio.h>

void logger(char *operation)
{
    static counter = 0;
    counter++;
    printf("[Logger]:%d %s\n", counter, operation);
}