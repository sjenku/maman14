
#include <stdlib.h>
#include "../headers/tools.h"
#include "../headers/queue.h"
#include "../headers/response.h"
#include "../headers/inputHandler.h"
#include "../headers/asmbOperation.h"
#include "../headers/engineCompile.h"
#include "../headers/engineDB.h"
#include "../headers/engineErrorChecker.h"
#include "../headers/dataGuidance.h"

/*this method takes the first word and second word in the line and ,
Check if the first word in the line is symbol and handle accordingly*/
void handleCaseFirstWordSymbol(char *word, char *nextWord, char *filename, int lineNumber)
{
    response *res;
    engineDB *db;
    db = getEngineDB();
    res = isSymbol(word);
    if (res == NULL)
        return;
    if (res->status == FAILURE)
    {
        /*this is not a symbol throw error to stdout*/
        loggerError(res->info, filename, lineNumber);
    }
    else
    {
        /*----------this is symbol handle symbol------------*/

        if (symbolExist(db->symbolsList, res->info)) /*check for duplicates*/
        {
            destroyResponse(res);                                            /*free old error*/
            res = newResponse(FAILURE, "can't duplicate labels '%s'", word); /*create new res message*/
            loggerError(res->info, filename, lineNumber);                    /*print to stdout*/
        }
        else /*insert the symbol after all checks*/
        {
            //TODO: handle insertion if there is second word operetion or data
            if (isDataGuidanceWord(nextWord))
                addSymbol(db->symbolsList, res->info, 0, ATTRIBUTE_DATA);
            else if (isOperationValid(nextWord))
            {
                addSymbol(db->symbolsList, res->info, 0, ATTRIBUTE_CODE);
            }
        }
    }
    destroyResponse(res);
}

/*this function set the workflow that actually the algorithm that handle each line*/
void engineWorkFlowForLine(char *line, int lineNumber, char *filename)
{
    queue *tmpQueue;
    char *word;
    char *nextWord;
    /*init temp queue that will hold the seperated words in the line*/
    tmpQueue = initQueue();
    /*seperate the line to words*/
    enqueueWordsFromString(tmpQueue, line);
    /*init memory for holding copy of the first elemnt data*/
    word = (char *)malloc(sizeDataFirstElement(tmpQueue));
    /*copy to 'word' the string that inside the first element of the queue*/
    display(tmpQueue->headP);
    peek(tmpQueue, &word);
    /*dequeue first element*/
    dequeue(tmpQueue);
    /*set the second word*/
    nextWord = (char *)malloc(sizeDataFirstElement(tmpQueue));
    peek(tmpQueue, &nextWord);
    /*Check if the first word in the line is symbol and handle accordingly*/
    handleCaseFirstWordSymbol(word, nextWord, filename, lineNumber);

    /*free memory*/
    destroyQueue(tmpQueue);
    free(word);
    free(nextWord);
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
    printSymbolsFrom(db->symbolsList->head);
    destroyEngineDB(db);
}
