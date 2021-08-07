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

    dataSeg *dataSeg;
    operetionSeg *oprSeg;
    symbolsList *symbolsList;

    loggerOn(I);
    loggerOn(D);

    dataSeg = getDataSegment();
    oprSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    runEngine(argc, argv);

    printSymbols(symbolsList);
    destroyDataSeg(dataSeg);
    destroySymbolsList(symbolsList);
    destroyOperetionSeg(oprSeg);

    /*char *str;
    str = (char *)malloc(26);
    numberToBinary(4, 25, &str);
    logger(D, "str => %s", str);
    free(str);
    */

    check_leaks();
    return 0;
}

// /* opcode|rs|rt|rd|funct|empty */
// dataSeg *dataSeg;
// operetionSeg *oprSeg;
// symbolsList *symbolsList;

// dataSeg = getDataSegment();
// oprSeg = getOperetionSegment();
// symbolsList = getSymbolsList();

// printSymbols(symbolsList);
// destroyDataSeg(dataSeg);
// destroySymbolsList(symbolsList);
// destroyOperetionSeg(oprSeg);
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
