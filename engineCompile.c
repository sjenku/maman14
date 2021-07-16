#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/tools.h"
#include "headers/queue.h"
#include "headers/inputHandler.h"
#include "headers/symbolList.h"
#include "headers/engineCompile.h"

int isCommentLine(char *line)
{
    /*Temperory char holder of each char in the line*/
    char *ch;
    /*Iterate threw the line*/
    for (ch = line; *ch != '\0'; ch++)
    {
        if (!isspace(*ch))
            /*Checking if the ';' char in the begining
         of the line that indecates that is a comment*/
            if (*ch == ';')
            {
                logger(I, "Is a comment Line => %s", line);
                return SUCCESS;
            }
    }
    return FAILURE;
}

int isOperationLine(const char *line)
{
    logger(L, "isOperetionLine");
    /*TODO:*/
    return FAILURE;
}

void runEngine(int argc, char *argv[])
{
    int (*rulesArr[TOTAL_RULES])(char *); /*Array of functions(Rules) applied to the each line*/
    static engineDB *db;                  /*the data base used as a connector between multiple methods used on input line*/
    logger(L, "ENGINE IS RUNNING");
    db = initEngineDB();
    if (db == NULL)
    {
        logger(E, "Memory issue,couldn't create enough memory for handle proccess of compiling");
    }
    else
    {
        logger(I, "Data base setted");
    }
    rulesArr[0] = isCommentLine;
    runRulessOnLinesOfFile(argc, argv, TOTAL_RULES, rulesArr);
}

/*This Method Return pointer to new DATABASE*/
engineDB *initEngineDB()
{
    /*Init pointer to the data base*/
    engineDB *db = (engineDB *)malloc(sizeof(engineDB));
    /*if not enough memory,return NULL*/
    if (db == NULL)
        return NULL;
    /*Init pointer to the queue*/
    db->queue = initQueue();
    /*handle not enough memory when allocating memory*/
    if (db->queue == NULL)
    {
        free(db);
        return NULL;
    }
    /*Init symbols list*/
    db->symbolsList = initSymbolsList();
    /*handle not enough memory during allocation of memory*/
    if (db->symbolsList == NULL)
    {
        free(db);
        return NULL;
    }
    /*return new Data Base for engine*/
    return db;
}

int freeEngineDB()
{
    /*TODO:=====>*/
    return 0;
}
