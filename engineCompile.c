
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "headers/tools.h"
#include "headers/inputHandler.h"
#include "headers/engineCompile.h"
#include "headers/stringSeperator.h"
#include "headers/symbolList.h"
#include "headers/dataSegment.h"
#include "headers/operetionSegment.h"
#include "headers/objectCreator.h"
#include "headers/extCreator.h"
#include "headers/errors.h"

/* private */
int insertDataSegmentToObjectList(dataSeg *seg, objList *objL);
int createEntFile();

/* this function set the workflow that actually the algorithm that handle each line */
void engineWorkFlowForLineFirst(char *line, int lineNumber, char *filename)
{
    /* variables */
    seperator *seperator;
    symbolsList *symbolsList;
    operetionSeg *operetionSeg;
    errors *errorsList;
    dataSeg *dataSeg;

    int flagSymbol, totalWords, wordIndex, length, status_response;
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
    /* create singelton errorsList that would hold errors accured during compiling */
    errorsList = getErrorList();
    /* set pointer to the first word */
    firstWord = getPointerToWord(seperator, 1);
    currentWord = getPointerToWord(seperator, wordIndex);
    totalWords = numberOfWords(seperator);

    /* if first word is NULL it's mean there was an empty line */
    if (currentWord != NULL && !isComment(currentWord))
    {
        /* check if valid symbol name ,if it is, move the index to look to the next word and set
        the symbol's flag to be true*/
        status_response = isValidSymbolName(currentWord);
        if (status_response == SUCCESS && !isSymbolExist(symbolsList, currentWord))
        {
            flagSymbol = TRUE;
            wordIndex++;
            currentWord = getPointerToWord(seperator, wordIndex);
        }
        /* this is not a valid symbol */
        else
        {
            /* it's mean that it must be symbol but is not so add error */
            if (totalWords == 3)
            {
                /* it's mean the symbol already exist ,create error (if symbol valid then it's mean it's duplicated symbol)*/
                if (status_response == SUCCESS)
                    insertErrorTo(errorsList, filename, lineNumber, currentWord, "can't duplicate symbols");
                else
                    insertErrorTo(errorsList, filename, lineNumber, currentWord, symbolErrorReason(status_response));
            }
        }

        /* set the rest line to check the values is valid for directive and opetions */
        restLine = concenateToStringFrom(seperator, wordIndex + 1);
        /* case directive word */
        if (isValidDirectiveName(currentWord))
        {
            status_response = isValidDirectiveValues(currentWord, restLine);
            if (status_response > 0)
            {
                /* insert symbol if there been first word symbol */
                if (flagSymbol == TRUE)
                    insertSymbol(symbolsList, firstWord, dataSeg->DC, ATTRIBUTE_DATA);

                /* insert directive word */
                insertDirectiveTo(dataSeg, currentWord, restLine);
            }
            /* it's not valid directive value ,insert error if status_response negative
                the reason for this check because isValidDirectiveValue return amount
                of values if they valid */
            else if (status_response < 0)
            {
                insertErrorTo(errorsList, filename, lineNumber, restLine, directiveErrorReason(status_response));
            }
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
    seperator *seperator;
    operetionSeg *operetionSeg;
    operetionNode *tmpOperetionNode;
    operetionInfo *tmpOperetionInfo;
    symbolsList *symbolList;
    symbolListNode *tmpSymbolListNode;
    extList *externalsList;
    objList *objectList;
    int wordIndex;
    /* set index that indicates which operetion to get from operetion segment */
    int operetionIndex = 0;
    /* create seperator that is seperating the line into individuals words */
    seperator = initSeprator();
    appendStringWithSpace(seperator, line);
    /* get the pointer to the symbolsList */
    symbolList = getSymbolsList();
    /* set initial val for tmpSymbolListNode that would point to the symbol from symbol list */
    tmpSymbolListNode = NULL;
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
                /* case that is external val */
                /* get the node for current operetion in line*/
                tmpOperetionNode = getPointToOpertionFromSeg(operetionSeg, operetionIndex);
                /* guard */
                if (tmpOperetionNode == NULL)
                    goto END;
                /* check if it's J type */
                tmpOperetionInfo = getOperetionInfo(tmpOperetionNode->name);
                if (tmpOperetionInfo->type == 'J')
                {
                    /* get the symbol node that mentioned as value */
                    tmpSymbolListNode = getPointerToSymbol(symbolList, getPointerToWord(seperator, wordIndex + 1));
                    /* check if this valid symbol and it's exist in the symbol list */
                    if (tmpSymbolListNode != NULL)
                    {
                        /* save the external symbol with the relative address for creating later .ext file*/
                        externalsList = getExtList();
                        insertExtTo(externalsList, tmpSymbolListNode->name, tmpOperetionNode->address - IC_INCREASER);
                    }
                }
                /* then check if the next word is external symbol */
                objectList = getObjectList();
                codeOperetionToBinary(objectList, tmpOperetionNode);
                /* this operetion no more relevant,delete from list */
                removeFirstOperetion(operetionSeg);
            }
        }
    }
END:
    destroySeperator(seperator);
}

void runEngine(int argc, char *argv[])
{
    void (*rulesFunc)(char *line, int lineNumber, char *filename); /*Array of functions(Rules) applied to handle each line*/
    operetionSeg *operetionSeg;
    symbolsList *symbolsList;
    dataSeg *dataSeg;
    objList *objectList;
    extList *extList;
    errors *errorsList;
    char *filename;
    int ICF, DCF, fileNumber;

    /* set all data holders relevant to compile */
    operetionSeg = getOperetionSegment();
    symbolsList = getSymbolsList();
    dataSeg = getDataSegment();
    objectList = getObjectList();
    extList = getExtList();
    errorsList = getErrorList();

    /* run this engine on each file */
    for (fileNumber = 1; fileNumber < argc; fileNumber++)
    {
        /* Set of functions that will be implemented on each line of the file*/
        rulesFunc = engineWorkFlowForLineFirst;
        filename = argv[fileNumber];
        runRulessOnLinesOfFile(filename, rulesFunc);
        printErrors(errorsList);
        /* if errors accured after first iteretion */
        if (isEmptyErrorList(errorsList))
        {
            /* Handle updating address in symbols with attribute 'data' and to dataSegment */
            ICF = operetionSeg->IC;
            DCF = dataSeg->DC;
            moveAddressDataSeg(dataSeg, ICF);
            moveAddressDataTypeSymbolsList(symbolsList, ICF);

            /* Start Second Workflow */
            rulesFunc = engineWorkFlowForLineSecond;
            runRulessOnLinesOfFile(filename, rulesFunc);

            /* Insert All Directives binary to objectListCreator */
            insertDataSegmentToObjectList(dataSeg, objectList);

            /* create .ob file */
            createObjDataToFile(objectList, ICF - INITIAL_ADDRESS, DCF, filename);
            /* create .ent file */
            createEntFile(filename);
            /* create .ext file */
            printExternals(extList);
            createExtFileFrom(extList, filename);
        }

        /* clear data holders for next file */
        removeAllOperetionsFrom(operetionSeg);
        removeAllSymbolsFrom(symbolsList);
        removeAllDataFrom(dataSeg);
        removeAllObjectsFrom(objectList);
        removeAllExternalsFrom(extList);
        removeAllErrors(errorsList);
    }
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
    int numOfCharsInValue;
    /* guard */
    if (seg == NULL || objL == NULL)
    {
        return FAILURE;
    }

    tmpNode = seg->head_p;
    while (tmpNode != NULL)
    {
        numOfCharsInValue = strlen(tmpNode->value);
        if (strcmp(tmpNode->name, ASCIZ) == 0)
        {
            directiveAscizToCode(objL, tmpNode->value);
        }
        else
        {
            directiveDbDhDwToCode(objL, tmpNode->name, tmpNode->value);
        }
        tmpNode = tmpNode->next;
    }
    return SUCCESS;
}

/* this method takes all symbols,iterate threw them and create file containing 
   address and symbols that declared as .entry */
int createEntFile(char *filename)
{

    symbolsList *symbols;
    symbolListNode *tmpNode;
    FILE *fileEnt;
    char *fname;
    symbols = getSymbolsList();
    /* guard */
    if (symbols->head_p == NULL)
        return FAILURE;

    fname = createFileNameWithExtension(filename, "ent");
    if (fname == NULL)
        return FAILURE;

    fileEnt = fopen(fname, "w");
    if (fileEnt == NULL)
    {
        free(fname);
        return FAILURE;
    }

    /* iterate threw the list of symbols */
    tmpNode = symbols->head_p;
    while (tmpNode != NULL)
    {
        if (strcmp(tmpNode->attribute, ATTRIBUTE_DATA_ENTRY) == 0)
        {
            fprintf(fileEnt, "%s 0%d\n", tmpNode->name, tmpNode->address);
        }
        tmpNode = tmpNode->next;
    }
    free(fname);
    return SUCCESS;
}
