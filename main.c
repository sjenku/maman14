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

    /* opcode|rs|rt|rd|funct|empty */
    dataSeg *dataSeg;
    operetionSeg *oprSeg;
    symbolsList *symbolsList;

    dataSeg = getDataSegment();
    oprSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    loggerOn(I);
    loggerOn(D);
    runEngine(argc, argv);

    changeAttribute(symbolsList, "MAIN", ATTRIBUTE_DATA_ENTRY);
    printSymbols(symbolsList);
    destroyDataSeg(dataSeg);
    destroySymbolsList(symbolsList);
    destroyOperetionSeg(oprSeg);
    check_leaks();
    return 0;
}

// int sizeOfBits, i, num, k;
// sizeOfBits = 5;
// i = 0;
// num = 33;
// loggerOn(I);
// for (i = sizeOfBits - 1; i >= 0; i--)
// {
//     k = num >> i;
//     if (k & 1)
//         printf("1");
//     else
//         printf("0");
// }
