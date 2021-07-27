#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/inputHandler.h"
#include "headers/labelList.h"
#include "headers/asmbOperation.h"
#include "headers/queue.h"
#include "headers/dataGuidance.h"
#include "headers/engineCompile.h"

void check_leaks();

int main(int argc, char *argv[])
{
    loggerOn(E);
    loggerOn(D);
    // queue *q;
    // q = initQueue();
    // char *line = "LIST:  .db  6,9";
    // char *restLine;
    runEngine(argc, argv);
    // restLine = (char *)malloc(strlen(line));
    // enqueueStringSeperateWith(q, line, SEPERATE_WITH_SPACE);
    // dequeue(q);
    // dequeue(q);
    // catToStringWithSpace(q, restLine);
    // printf("test => %s\n", restLine);

    // check_leaks();
    return 0;
}
