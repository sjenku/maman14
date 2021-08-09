#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/tools.h"

/*Array of total logger types, the indexes of the array relative to the enum 'LoggerType',
for example if client intrested in the logger be on to specific type,it's handled by calling 'loggerOn' method that changes
the index of relative to the enum logger type to 1*/
static int switchers[TOTAL_LOGGER_TYPES];

void loggerOn(int loggerType)
{
    if (loggerType >= 0 && loggerType <= TOTAL_LOGGER_TYPES)
    {
        switchers[loggerType] = 1;
    }
}

void loggerOff(int loggerType)
{
    if (loggerType >= 0 && loggerType <= TOTAL_LOGGER_TYPES)
    {
        switchers[loggerType] = 0;
    }
}

/*
void loggerError(const char *errorInfo, const char *filename, int lineNumber)
{
    printf("[ERROR][FILENAME]:%s[LINE]:%d,%s\n", filename, lineNumber, errorInfo);
}*/

void logger(int loggerType, const char *format, ...)
{
    va_list args;
    if (switchers[loggerType]) /*checking if the switcher for loggertype is ON*/
    {
        va_start(args, format);
        switch (loggerType)
        {
        case 0:
            printf("[Logger]:");
            break;
        case 1:
            printf("[INFO]:");
            break;
        case 2:
            printf("[ERROR]:");
            break;
        case 3:
            printf("[DEBUG]:");
            break;
        }
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
}

int isSignNumberOrNumber(char *str)
{
    int flagSing;
    char *ch;
    ch = str;

    flagSing = FALSE;
    while (*ch != '\0')
    {
        if ((*ch) == '-' || (*ch) == '+')
        {
            if (flagSing == TRUE)
                return FAILURE;
            else
            {
                flagSing = TRUE;
                ch++;
            }
        }
        else if (!isnumber(*ch))
        {
            return FAILURE;
        }
        else
        {
            ch++;
            flagSing = FALSE;
        }
    }
    /* check the last number */
    if (flagSing == TRUE)
        return FAILURE;
    else
        return SUCCESS;
}

int isNumbersOrLetters(char *str)
{
    char *ch;
    int goodChar;
    ch = str;

    while (*ch != '\0')
    {
        goodChar = (isnumber(*ch) || ((*ch) >= 'a' && (*ch) <= 'z') || ((*ch) >= 'A' && (*ch) <= 'Z'));
        if (!goodChar)
            return FAILURE;
        ch++;
    }
    return SUCCESS;
}

/* isRegister check if the value is valid register number and if it does
it return number of the register otherwise it return FAILURE */
int isRegister(char *str)
{
    /* variables */
    char *ch;
    int number, length, factor;

    /* initiate variables */
    ch = str;
    length = strlen(str);
    factor = 1;

    /* ignore the space in the begining */
    while (isspace(*ch))
        ch++;

    /* check the first letter is '$' sign */
    if ((*ch) != '$')
        return FAILURE;

    /* if it's dollar sing go to else block */
    else
    {
        /* set ch to point on the last char */
        ch = str + length - 1;

        /* ignore the space from the end of the str */
        while (isspace(*ch))
            ch--;

        /* remaining till the $ sign should be number,check for it */
        /* TODO: FIX BUG - if there is 2 sign of dollars it would show that valid */
        while (*ch != '$')
        {
            /* check for each ch that it's a number */
            if (!isnumber(*ch))
                return FAILURE;
            ch--;
        }

        number = atoi(ch + 1);
        /* register can be from 1 till 32 */
        if (number >= 1 && number <= MAX_REGISTER)
            return number;
        else
            return FAILURE;
    }
}

/* the sizeOfBits represent how much bits would like to encode into, however 
the codedString need to be allocated with memory sizeOfBits + 1,to be able to include null char */
int numberToBinary(int numValue, int sizeOfBits, char **codedString)
{
    int k, indexString, i;
    /* check valid param and that codedString have enough memory to hold the coded num */
    if (codedString == NULL)
        return FAILURE;

    for (indexString = 0, i = sizeOfBits - 1; i >= 0; i--, indexString++)
    {
        k = numValue >> i;
        if (k & 1)
            (*codedString)[indexString] = '1';
        else
            (*codedString)[indexString] = '0';
    }
    (*codedString)[indexString] = '\0';
    return SUCCESS;
}

/* this method return new allocated char* with hex representation of binary input 
   this is a client responsobility to free memory that been allocated for the return value*/
char *binaryToHex(const char *inStr)
{
    static char hexlookup[] = "0123456789ABCDEF";
    char *outStr, *ch;
    int len = strlen(inStr) / 4;
    int i = strlen(inStr) % 4;
    outStr = (char *)malloc(len + i + 1); /* this would hold the output hex */
    ch = outStr;                          /* for move threw the output char* */
    char current = 0;
    if (i)
    { /* handle part that not devided by 4 */
        while (i--)
        {
            current = (current << 1) + (*inStr - '0');
            inStr++;
        }
        *ch = hexlookup[current];
        ++ch;
    }
    while (len--)
    {
        current = 0;
        for (i = 0; i < 4; ++i)
        {
            current = (current << 1) + (*inStr - '0');
            inStr++;
        }
        *ch = hexlookup[current];
        ++ch;
    }
    *ch = '\0'; // null char
    return outStr;
}
