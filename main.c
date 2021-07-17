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
    loggerOn(D);

    runEngine(argc, argv);
    check_leaks();
    return 0;
}
