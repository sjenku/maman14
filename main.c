#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/stringSeperator.h"

void check_leaks();

int main(int argc, char *argv[])
{
    seperator *sep;
    loggerOn(I);

    sep = initSeprator();
    appendString(sep, "Hello my name is Jenia");
    removeFirstWord(sep);
    displaySeperator(sep);
    destroySeperator(sep);
    check_leaks();
    return 0;
}
