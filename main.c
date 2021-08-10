#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <math.h>
#include "headers/tools.h"
#include "headers/stringSeperator.h"
#include "headers/errors.h"
#include "headers/operetionSegment.h"
#include "headers/symbolList.h"
#include "headers/dataSegment.h"
#include "headers/engineCompile.h"
#include "headers/objectCreator.h"

void check_leaks();

/*
    loggerOn(I);
    loggerOn(D);

    char *str;
    str = (char *)malloc((SIZE_BYTE * 4) * 2 + 1);
    directiveDbDhDwToCode(DW, "31,-12", &str);
    logger(D, "str => %s", str);
    free(str);
    */
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

    printDataSeg(dataSeg);
    destroyDataSeg(dataSeg);
    destroySymbolsList(symbolsList);
    destroyOperetionSeg(oprSeg);
    return 0;
}

/*
    dataSeg *dataSeg;
    operetionSeg *oprSeg;
    symbolsList *symbolsList;

    loggerOn(I);
    loggerOn(D);

    dataSeg = getDataSegment();
    oprSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    runEngine(argc, argv);


    printDataSeg(dataSeg);
    destroyDataSeg(dataSeg);
    destroySymbolsList(symbolsList);
    destroyOperetionSeg(oprSeg); */
