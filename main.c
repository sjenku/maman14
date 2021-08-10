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

int main(int argc, char *argv[])
{

    dataSeg *dataSeg;
    operetionSeg *oprSeg;
    symbolsList *symbolsList;
    objList *objectList;

    loggerOn(I);
    loggerOn(D);

    dataSeg = getDataSegment();
    oprSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    objectList = getObjectList();
    runEngine(argc, argv);

    printDataSeg(dataSeg);
    destroyDataSeg(dataSeg);
    destroySymbolsList(symbolsList);
    destroyOperetionSeg(oprSeg);
    destroyObjList(objectList);
    check_leaks();

    return 0;
}

// loggerOn(D);
// loggerOn(I);
// logger(D, "str %s", binaryToHex("0110000101000010", 0));
