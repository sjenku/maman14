
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
void handleCaseFirstWordLabel(const char *word, const char *secondWord, char *restLine, const char *filename, int lineNumber)
{
    char *label;
    engineDB *db;
    int length, numOfDataElements;
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
        if (isDataGuidanceWord(secondWord))
        {
            numOfDataElements = isValidData(secondWord, restLine);
            addLabel(db->labelsList, label, db->DC, ATTRIBUTE_DATA);
            /* 'allocates' the size for the data type */
            db->DCF = db->DC;
            db->DC += sizeOfGuidanceDataType(secondWord) * numOfDataElements;
        }
        else if (isOperationValid(secondWord))
        {
            addLabel(db->labelsList, label, db->IC, ATTRIBUTE_CODE);
            incrementEngineDbIC(db);
        }
    }
    free(label);
}

void handleFirstWordOperation(const char *word, const char *filename, int lineNumber)
{
    engineDB *db;

    db = getEngineDB();

    /* increment instruction counter */
    incrementEngineDbIC(db);
}

/* this function set the workflow that actually the algorithm that handle each line */
void engineWorkFlowForLine(char *line, int lineNumber, char *filename)
{
    queue *tmpQueue;
    char *word;
    int type;
    char *secondWord;
    char *restLine;

    /* check if the line is empty */
    if (line != NULL || strcmp(line, "") != 0)
    {
        /* init temp queue that will hold the seperated words in the line */
        /* seperate the line to words */
        /* init memory for holding copy of the first elemnt data */
        /* copy to word first second and third the string that inside the first element of the queue */
        tmpQueue = initQueue();
        enqueueStringSeperateWith(tmpQueue, line, SEPERATE_WITH_SPACE);

        /* first word */
        word = (char *)malloc(sizeDataFirstElement(tmpQueue));
        peek(tmpQueue, &word);
        dequeue(tmpQueue);

        /* set the second word */
        secondWord = (char *)malloc(sizeDataFirstElement(tmpQueue));
        peek(tmpQueue, &secondWord);
        dequeue(tmpQueue);

        /* get the remaining line and cancenateing it back from the remaining seperated words*/
        restLine = (char *)malloc(strlen(line));
        if (!isEmpty(tmpQueue))
        {
            display(tmpQueue->headP);
            catToStringWithSpace(tmpQueue, restLine);
        }
        /* get the type of the first word to handle accordingly */
        type = wordType(word, filename, lineNumber);
        switch (type)
        {
        case TYPE_LABEL:
            handleCaseFirstWordLabel(word, secondWord, restLine, filename, lineNumber);
            //TODO: Iterate threw all labels and add ICF to all data attributes
        case TYPE_COMMENT:
            break;
        case TYPE_OPERATION:
            handleFirstWordOperation(word, filename, lineNumber);
            break;
        default:
            break;
        }

        /* free memory */
        free(word);
        free(secondWord);
        free(restLine);
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
