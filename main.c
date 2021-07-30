#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/stringSeperator.h"
#include "headers/errors.h"
#include "headers/operetionSegment.h"

void check_leaks();

int main(int argc, char *argv[])
{

    loggerOn(I);
    loggerOn(E);

    operetionSeg *seg;
    seg = initOperetionSegment();
    insertOperetionTo(seg, "add", "3,4,33");
    insertOperetionTo(seg, "hey", "2,41,13");
    printOperetionsSeg(seg);

    /*  errors *errs;


    errs = initErrorsList();
    insertErrorTo(errs, 200, "Hello This is Greate Error!");
    insertErrorTo(errs, 400, "Naaaaa This Is Badddd?");
    insertErrorTo(errs, 200, "sdsdsdsd");
    printErrors(errs);
    destroyErrorsList(errs); */

    // check_leaks();
    return 0;
}
