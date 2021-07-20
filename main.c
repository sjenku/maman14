#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/inputHandler.h"
#include "headers/symbolList.h"
#include "headers/asmbOperation.h"
#include "headers/queue.h"
#include "headers/engineCompile.h"

void check_leaks();

int main(int argc, char *argv[])
{
    loggerOn(E);
    loggerOn(D);

    // runEngine(argc, argv);
    queue *q = initQueue();
    enqueueWordsFromString(q, "LOOP: ori	$9,-5,$2");
    display(q->headP);
    // check_leaks();
    return 0;
}
