
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/tools.h"
#include "headers/inputHandler.h"
#include "headers/engineCompile.h"
#include "headers/stringSeperator.h"
#include "headers/symbolList.h"
#include "headers/dataSegment.h"

/* this method takes the first word label and second word in the line and insert if no duplicates to the data base */
void handleCaseFirstWordLabel(const char *word, const char *secondWord, char *restLine, const char *filename, int lineNumber)
{
}

void handleFirstWordOperation(const char *word, const char *filename, int lineNumber)
{
}

/* this function set the workflow that actually the algorithm that handle each line */
void engineWorkFlowForLine(char *line, int lineNumber, char *filename)
{
    /* variables */
    seperator *seperator;
    symbolsList *symbolsList;

    int flagSymbol, IC, DC;
    char *firstWord;
    char *secWord;
    char *thirdWord;

    /* create symbol list that would hold the symbols */
    symbolsList = getSymbolsList();
    /* create seperator that is seperating the line into individuals words */
    seperator = initSeprator();
    appendString(seperator, line);

    /* set pointer to the first word */
    firstWord = getPointerToWord(seperator, 1);

    /* if first word is NULL it's mean there was an empty line */
    if (firstWord != NULL && !isComment(firstWord))
    {
        /* check if valid symbol name */
        if (isValidSymbolName(firstWord) == SUCCESS && !isSymbolExist(symbolsList, firstWord))
        {
            secWord = getPointerToWord(seperator, 2);
            if (isValidDirectiveName(secWord))
                insertSymbol(symbolsList, firstWord, 100, ATTRIBUTE_DATA);
        }
        else
        {
        }
    }

    /* free memory */
    destroySeperator(seperator);
}

void runEngine(int argc, char *argv[])
{
    void (*rulesArr[TOTAL_RULES])(char *line, int lineNumber, char *filename); /*Array of functions(Rules) applied to handle each line*/

    /*Set of functions that will be implemented on each line of the file*/
    rulesArr[0] = engineWorkFlowForLine;
    runRulessOnLinesOfFile(argc, argv, TOTAL_RULES, rulesArr);
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
                logger(I, "Is a comment word => %s", word);
                return SUCCESS;
            }
    }
    return FAILURE;
}
