#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/stringSeperator.h"
#include "headers/errors.h"
#include "headers/operetionSegment.h"
#include "headers/symbolList.h"
#include "headers/dataSegment.h"
#include "headers/engineCompile.h"

void check_leaks();

int main(int argc, char *argv[])
{

    seperator *seperator;
    char *resultedString;
    loggerOn(I);
    loggerOn(E);
    seperator = initSeprator();
    appendString(seperator, "s , , , ");
    resultedString = concenateToStringFrom(seperator, 1);
    logger(I, "the string => %s", resultedString);
    if (resultedString != NULL)
        free(resultedString);
    destroySeperator(seperator);
    check_leaks();
    return 0;
}
