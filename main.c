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

    /*------------Create Symbols List-------------
     symbolsList *symbols = (symbolsList *)malloc(sizeof(symbolsList)); //TODO:Free malloc

     addSymbol(symbols, "Jhon", 100);
     addSymbol(symbols, "Jessica", 104);
     addSymbol(symbols, "George", 112);

     printSymbolsFrom(symbols->head);

     free(symbols);

    readPrintLineFile(argc, argv);

     isOperationExist("or") ? printf("or exist\n") : printf("or not exist");
     isOperationExist("add") ? printf("add exist\n") : printf("add not exist");
     isOperationExist("stop") ? printf("stop exist\n") : printf("stop not exist");
     isOperationExist("blabla") ? printf("blabla exist\n") : printf("blabla not exist");
    */
    /*runEngine(argc, argv);*/
    engineWorkFlow("hello:Wor qbcs");
    /*check_leaks();*/
    return 0;
}
