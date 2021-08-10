
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/tools.h"
#include "headers/inputHandler.h"
#include "headers/engineCompile.h"
#include "headers/stringSeperator.h"
#include "headers/symbolList.h"
#include "headers/dataSegment.h"
#include "headers/operetionSegment.h"
#include "headers/objectCreator.h"

/* private */
int insertDataSegmentToObjectList(dataSeg *seg, objList *objL);

/* this function set the workflow that actually the algorithm that handle each line */
void engineWorkFlowForLineFirst(char *line, int lineNumber, char *filename)
{
    /* variables */
    seperator *seperator;
    symbolsList *symbolsList;
    operetionSeg *operetionSeg;
    dataSeg *dataSeg;

    int flagSymbol, wordIndex, length;
    char *firstWord;
    char *tmpWord;
    char *currentWord;
    char *restLine;

    /* set flag */
    flagSymbol = FALSE;
    /* set index to know on witch word we looking at */
    wordIndex = 1;
    /* create symbol list that would hold the symbols */
    symbolsList = getSymbolsList();
    /* get pointer to dataSegment that would hold the directives and their values */
    dataSeg = getDataSegment();
    /* get pointer to operetionSegment that would hold the operetions and their values */
    operetionSeg = getOperetionSegment();
    /* create seperator that is seperating the line into individuals words */
    seperator = initSeprator();
    appendStringWithSpace(seperator, line);

    /* set pointer to the first word */
    firstWord = getPointerToWord(seperator, 1);
    currentWord = getPointerToWord(seperator, wordIndex);

    /* if first word is NULL it's mean there was an empty line */
    if (currentWord != NULL && !isComment(currentWord))
    {
        /* check if valid symbol name ,if it is, move the index to look on the next word and set
        the symbol's flag to be true*/
        if (isValidSymbolName(currentWord) == SUCCESS && !isSymbolExist(symbolsList, currentWord))
        {
            flagSymbol = TRUE;
            wordIndex++;
            currentWord = getPointerToWord(seperator, wordIndex);
        }

        /* set the rest line to check the values is valid for directive and opetions */
        restLine = concenateToStringFrom(seperator, wordIndex + 1);
        /* case directive word */
        if (isValidDirectiveName(currentWord) && isValidDirectiveValues(currentWord, restLine))
        {
            /* insert symbol if there been first word symbol */
            if (flagSymbol == TRUE)
                insertSymbol(symbolsList, firstWord, dataSeg->DC, ATTRIBUTE_DATA);

            /* insert directive word */
            insertDirectiveTo(dataSeg, currentWord, restLine);
        }
        /* handle case the word is .external */
        else if (isExternal(currentWord))
        {
            currentWord = getPointerToWord(seperator, wordIndex + 1);
            /* check if symbol valid, if true insert it with attribute .external */
            if (currentWord != NULL)
            {
                /* create tmpSymbol with adding ':' */
                length = strlen(currentWord) + 2; /* +2 stends for adding ':' and '\0' */
                tmpWord = (char *)malloc(length);
                strcpy(tmpWord, currentWord);
                tmpWord[length - 2] = ':';
                tmpWord[length - 1] = '\0';
                /* check if it's valid symbol name and there is no more symbols with same name*/
                if (isValidSymbolName(tmpWord) && !isSymbolExist(symbolsList, tmpWord))
                    insertSymbol(symbolsList, tmpWord, 0, ATTRIBUTE_EXTERNAL);
                free(tmpWord);
            }
        }
        else if (isValidOperationName(currentWord))
        {
            if (flagSymbol == TRUE)
            {
                insertSymbol(symbolsList, firstWord, operetionSeg->IC, ATTRIBUTE_CODE);
            }
            insertOperetionTo(operetionSeg, currentWord, restLine);
        }
        /* free memory */
        if (restLine != NULL)
            free(restLine);
    }
    /* free memory */
    destroySeperator(seperator);
}

/* ============================ SECOND WORKFLOW ================================= */
void engineWorkFlowForLineSecond(char *line, int lineNumber, char *filename)
{
    char *firstWord, *currentWord, *symbolName;
    char *codedBin;
    seperator *seperator;
    operetionSeg *operetionSeg;
    symbolsList *symbolList;
    objList *objectList;
    int wordIndex;
    /* set index that indicates which operetion to get from operetion segment */
    static int operetionIndex = 0;
    /* create seperator that is seperating the line into individuals words */
    seperator = initSeprator();
    appendStringWithSpace(seperator, line);
    /* get the pointer to the symbolsList */
    symbolList = getSymbolsList();
    /* get the pointer to the saved operetions from the first workflow */
    operetionSeg = getOperetionSegment();
    /* set index to know on witch word we looking at */
    wordIndex = 1;
    /* set pointer to the first word */
    firstWord = getPointerToWord(seperator, 1);
    currentWord = getPointerToWord(seperator, wordIndex);

    /* if first word is NULL it's mean there was an empty line */
    if (currentWord != NULL && !isComment(currentWord))
    {
        /* check if the word is symbol,if it does, move to the next word */
        if (isValidSymbolName(currentWord) == SUCCESS)
        {
            wordIndex++;
            currentWord = getPointerToWord(seperator, wordIndex);
        }
        /* if it's directive code to binary */
        if (isValidDirectiveName(currentWord))
        {
            goto END;
        }
        else
        {
            if (isEntry(currentWord))
            {
                symbolName = getPointerToWord(seperator, wordIndex + 1);
                changeAttribute(symbolList, symbolName, ATTRIBUTE_DATA_ENTRY);
            }
            /* it's operetion , code it to binary and print it*/
            else
            {

                codedBin = codeOperetionToBinary(operetionSeg, operetionIndex);
                logger(D, "it's here2 %s", codedBin);
                /* insert to objectList for manage it after when creating file.ob */
                objectList = getObjectList();
                insertBinaryToObj(objectList, STYLE_OPERETION, codedBin);
                /* free memory */
                free(codedBin);
                operetionIndex++;
            }
        }
    }
END:
    destroySeperator(seperator);
}

void runEngine(int argc, char *argv[])
{
    void (*rulesArr[TOTAL_RULES])(char *line, int lineNumber, char *filename); /*Array of functions(Rules) applied to handle each line*/
    operetionSeg *operetionSeg;
    symbolsList *symbolsList;
    dataSeg *dataSeg;
    objList *objectList;
    int ICF;

    operetionSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    dataSeg = getDataSegment();
    objectList = getObjectList();

    /* Set of functions that will be implemented on each line of the file*/
    rulesArr[0] = engineWorkFlowForLineFirst;
    runRulessOnLinesOfFile(argc, argv, TOTAL_RULES, rulesArr);

    /* Handle updating address in symbols with attribute 'data' and to dataSegment */
    ICF = operetionSeg->IC;
    moveAddressDataSeg(dataSeg, ICF);
    moveAddressDataTypeSymbolsList(symbolsList, ICF);

    /* Start Second Workflow */
    rulesArr[0] = engineWorkFlowForLineSecond;
    runRulessOnLinesOfFile(argc, argv, TOTAL_RULES, rulesArr);

    /* Insert All Directives binary to objectListCreator */
    insertDataSegmentToObjectList(dataSeg, objectList);
    /* create .ob file */
    createObjDataToFile(objectList);
}

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
                return SUCCESS;
            }
    }
    return FAILURE;
}

int insertDataSegmentToObjectList(dataSeg *seg, objList *objL)
{
    directiveNode *tmpNode;
    char *binStr;
    int numOfCharsInValue;
    /* guard */
    if (seg == NULL || objL == NULL)
    {
        return FAILURE;
    }

    printDataSeg(seg);
    tmpNode = seg->head_p;
    while (tmpNode != NULL)
    {
        numOfCharsInValue = strlen(tmpNode->value);
        binStr = (char *)malloc(((SIZE_BYTE * directiveTypeSize(tmpNode->name))) * numOfCharsInValue + 1);
        if (strcmp(tmpNode->name, ASCIZ) == 0)
        {
            directiveAscizToCode(tmpNode->value, numOfCharsInValue, &binStr);
            logger(D, "1address=> %d  bin=>%s", tmpNode->address, binStr);
        }
        else
        {

            directiveDbDhDwToCode(tmpNode->name, tmpNode->value, &binStr);
            logger(D, "2address=> %d  bin=>%s", tmpNode->address, binStr);
        }
        if (strcmp(tmpNode->name, ASCIZ) == 0)
            insertBinaryToObj(objL, STYLE_DIFF, binStr);
        else
            insertBinaryToObj(objL, STYLE_DATA, binStr);
        free(binStr);
        tmpNode = tmpNode->next;
    }
    printObjList(objL);
    return SUCCESS;
}
