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
#include "headers/extCreator.h"

void check_leaks();

int main(int argc, char *argv[])
{

    dataSeg *dataSeg;
    operetionSeg *oprSeg;
    symbolsList *symbolsList;
    objList *objectList;
    extList *extL;

    loggerOn(I);
    loggerOn(D);
    loggerOn(E);

    dataSeg = getDataSegment();
    oprSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    objectList = getObjectList();
    extL = getExtList();
    runEngine(argc, argv);

    printDataSeg(dataSeg);
    printSymbols(symbolsList);
    destroyDataSeg(dataSeg);
    destroySymbolsList(symbolsList);
    destroyOperetionSeg(oprSeg);
    destroyObjList(objectList);
    destroyExternalsList(extL);
    check_leaks();

    return 0;
}

// loggerOn(D);
// loggerOn(I);
// logger(D, "str %s", binaryToHex("0110000101000010", 0));
