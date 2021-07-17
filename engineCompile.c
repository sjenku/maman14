#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "headers/errors.h"
#include "headers/tools.h"
#include "headers/queue.h"
#include "headers/inputHandler.h"
#include "headers/symbolList.h"
#include "headers/asmbOperation.h"
#include "headers/engineCompile.h"

int isComment(char *word)
{
    /*Temperory char holder of each char in the line*/
    char *ch;
    /*Iterate threw the line*/
    for (ch = word; *ch != '\0'; ch++)
    {
        if (!isspace(*ch))
            /*Checking if the ';' char in the begining
         of the line that indecates that is a comment*/
            if (*ch == ';')
            {
                logger(I, "Is a comment word => %s", word);
                return SUCCESS;
            }
    }
    return FAILURE;
}

int isOperation(const char *word)
{
    return isOperationValid(word);
}

error *isSymbol(char *word)
{
    char *ch;     /*for handle each char in the word*/
    int position; /*position of the current char*/
    char *tmpStr; /*hold temerory substring from begining of the word till ':'*/
    error *err;
    if (word == NULL)
        return NULL;
    /*Iterate threw the word*/
    for (ch = word, position = 0; (*ch) != '\0'; ch++, position++)
    {
        /*checking if the letter is ':' if it does then make substring till that char*/
        if ((*ch) == ':')
        {
            /*creating the substring till ':'*/
            tmpStr = (char *)malloc(position + 1);
            strncpy(tmpStr, word, position);
            /*checking if the word till the ':' char isn't a reserved word for assembly operetions */
            if (isOperation(tmpStr))
            {
                /* logger(E, "[file]:%s,[line]:%d : Can't be used '%s' as a symbol,this is an operation name", filename, lineNumber, tmpStr);*/
                err = newError(1, "Can't be used '%s' as a symbol,this is an operation name", tmpStr);
                free(tmpStr);
                return err;
            }
            ch = (word + position + 1);        /*check the next letter after ':'*/
            if ((*ch != '\0') && (*ch != ' ')) /*label should end with ';'*/
            {
                /* logger(E, "[file]:%s,[line]:%d :label should end with ':',label can't finish with a letter '%c'", filename, lineNumber, *ch);*/
                err = newError(1, "label should end with ':',label can't finish with a letter '%c'", *ch);
                free(tmpStr);
                return err;
            }
            /*save the word*/
            free(tmpStr);
            err = newError(0, "");
            return err;
        }
    }
    return NULL;
}

/*this function set the workflow that actually the algorithm that handle each line*/
void engineWorkFlowForLine(char *line, int lineNumber, char *filename)
{
    queue *tmpQueue;
    char *word;
    error *err;
    static engineDB *db;
    /*init temp queue that will hold the seperated words in the line*/
    tmpQueue = initQueue();

    db = getEngineDB();

    /*seperate the line to words*/
    enqueueWordsFromString(tmpQueue, line);
    /*init memory for holding copy of the first elemnt data*/
    word = (char *)malloc(sizeDataFirstElement(tmpQueue));
    /*copy to 'word' the string that inside the first element of the queue*/
    peek(tmpQueue, &word);
    /*Check if the first word in the line is symbol*/
    err = isSymbol(word);
    if (err != NULL && err->status == 1)
    {
        /*this is not a symbol throw error to stdout*/
        loggerError(err->info, filename, lineNumber);
    }
    else if (err != NULL)
    {
        /*this is symbol handle symbol*/
        logger(D, "Added dymbol to %p", db->symbolsList);
        addSymbol(db->symbolsList, word, 0);
    }
    /*free memory*/
    destroyError(err);
    destroyQueue(tmpQueue);
    free(word);
}
void runEngine(int argc, char *argv[])
{
    void (*rulesArr[TOTAL_RULES])(char *line, int lineNumber, char *filename); /*Array of functions(Rules) applied to handle each line*/
    /*init the data base used as a connector between multiple methods used on input line*/
    engineDB *db;
    db = getEngineDB(); /*TODO:RENAME IT TO THE GET - AND HANDLE IN initEngineDB*/
    logger(L, "ENGINE IS RUNNING");
    if (db == NULL)
    {
        logger(E, "Memory issue,couldn't create enough memory to handle proccess of compiling");
    }
    else
    {
        logger(I, "Data base setted");
    }
    /*Set of functions that will be implemented on each line of the file*/
    rulesArr[0] = engineWorkFlowForLine;
    runRulessOnLinesOfFile(argc, argv, TOTAL_RULES, rulesArr);
    /*free memory*/
    logger(D, "SYMBOLS=>");
    printSymbolsFrom(db->symbolsList->head);
    destroyEngineDB(db);
}

/*return the data base used as a connector between multiple methods used on input line*/
engineDB *getEngineDB()
{
    static engineDB *db;
    if (db == NULL)
        db = initEngineDB();
    return db;
}

void destroyEngineDB(engineDB *db)
{
    if (db == NULL)
        return;

    destroyQueue(db->queue);
    destorySymbolList(db->symbolsList);
    free(db);
}

/*This Method Return pointer to new DATABASE*/
engineDB *initEngineDB()
{
    engineDB *db;
    /*Init pointer to the data base*/
    db = (engineDB *)malloc(sizeof(engineDB));
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
