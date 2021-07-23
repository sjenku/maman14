
#include <stdlib.h>
#include <string.h>
#include "../headers/tools.h"
#include "../headers/queue.h"
#include "../headers/response.h"
#include "../headers/inputHandler.h"
#include "../headers/asmbOperation.h"
#include "../headers/engineCompile.h"
#include "../headers/engineDB.h"
#include "../headers/engineChecker.h"
#include "../headers/dataGuidance.h"

/* this method takes the first word label and second word in the line and insert if no duplicates to the data base */
void handleCaseFirstWordLabel(const char *word, const char *nextWord, const char *filename, int lineNumber)
{
    char *label;
    engineDB *db;
    int length;
    response *res;

    /* get pointer to the data base */
    db = getEngineDB();
    /* extract the label from word (without ':') */
    length = strlen(word);
    label = (char *)malloc(length);
    strcpy(label, word);
    *(label + length - 1) = '\0';
    /*----------this is label handle label------------*/
    if (labelExist(db->labelsList, label)) /*check for duplicates*/
    {
        res = newResponse("[FILENAME]:%s,[LINE]:%d,can't duplicate labels '%s'", filename, lineNumber, word); /*create new res message*/
        /* enqueue response error to the errors queue in the data base */
        enqueue(db->errorsQueue, res->info);
        /* free memory */
        destroyResponse(res);
    }
    else /*insert the label after all checks*/
    {
        if (isDataGuidanceWord(nextWord))
            addLabel(db->labelsList, label, 0, ATTRIBUTE_DATA);
        else if (isOperationValid(nextWord))
            addLabel(db->labelsList, label, 0, ATTRIBUTE_CODE);
    }
    free(label);
}

void handleFirstWordOperation(const char *word, const char *filename, int lineNumber)
{
    engineDB *db;

    db = getEngineDB();
    /* increment instruction counter */
    incrementIC(db);
}

/* this function set the workflow that actually the algorithm that handle each line */
void engineWorkFlowForLine(char *line, int lineNumber, char *filename)
{
    queue *tmpQueue;
    char *word;
    int type;
    char *nextWord;
    /* check if the line is empty */
    if (line != NULL || strcmp(line, "") != 0)
    {
        /* init temp queue that will hold the seperated words in the line */
        tmpQueue = initQueue();
        /* seperate the line to words */
        enqueueWordsFromString(tmpQueue, line);
        /* init memory for holding copy of the first elemnt data */
        word = (char *)malloc(sizeDataFirstElement(tmpQueue));
        /* copy to 'word' the string that inside the first element of the queue */
        peek(tmpQueue, &word);
        /* dequeue first element */
        dequeue(tmpQueue);
        /* set the second word */
        nextWord = (char *)malloc(sizeDataFirstElement(tmpQueue));
        peek(tmpQueue, &nextWord);

        /* get the type of the first word to handle accordingly */
        type = wordType(word, filename, lineNumber);

        switch (type)
        {
        case TYPE_LABEL:
            handleCaseFirstWordLabel(word, nextWord, filename, lineNumber);
            break;
        case TYPE_COMMENT:
            handleFirstWordOperation(word, filename, lineNumber);
            break;
        case TYPE_OPERATION:
            break;
        default:
            break;
        }

        // if (!isComment(word))
        // {
        //     /* check if the first word in the line is label and handle accordingly */
        //     res = isLabel(word);
        //     printf("Is Label?\n");
        //     if (res->status == SUCCESS)
        //         handleCaseFirstWordLabel(word, nextWord, filename, lineNumber);
        //     else
        //     {
        //         if (isOperation(word))
        //             printf("This is operation => %s\n", word);
        //     }
        // }
        /* free memory */
        free(word);
        free(nextWord);
        destroyQueue(tmpQueue);
    }
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
    printLabelsFrom(db->labelsList->head);
    /* print errors */
    display(db->errorsQueue->headP);
    destroyEngineDB(db);
}
