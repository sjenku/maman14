#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/tools.h"
#include "../headers/objectCreator.h"

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
it return number of the register otherwise it return REG_FAILURE that's equalant to -1 int */
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
        return REG_FAILURE;

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
                return REG_FAILURE;
            ch--;
        }

        number = atoi(ch + 1);
        /* register can be from 0 till 31 */
        if (number >= 0 && number <= MAX_REGISTER)
            return number;
        else
            return REG_FAILURE;
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
   this is a client responsobility to free memory that been allocated for the return value
   the reading from binary happens from right to left*/
char *binaryToHex(char *inStr, int fromRight)
{
    static char hexlookup[] = "0123456789ABCDEF";
    char *outStr, tmp, *ch, *endP;
    char current;
    int i, len;
    /* endP points to the end of the inStr */
    endP = inStr + strlen(inStr) - 1;
    /* holding the number of chuncks of 4 bits */
    len = (strlen(inStr)) / 4;
    /* holding the remain bits that out of 4 chuncks */
    i = (strlen(inStr)) % 4;
    /* the string that would be return to the client */
    outStr = (char *)malloc(len + i + 1); /* this would hold the output hex */
    ch = outStr;                          /* for move threw the output char* */
    current = 0;
    if (i)
    { /* handle part that not devided by 4 */
        while (i--)
        {
            current = (current << 1) + (*endP - '0');
            endP--;
        }
        *ch = hexlookup[(int)current];
        ++ch;
    }
    while (len--)
    {
        current = 0;
        if (fromRight)
        {
            endP = endP - 3;
            for (i = 0; i < 4; ++i)
            {
                current = (current << 1) + (*endP - '0');
                endP++;
            }
            endP = endP - 5;
            *ch = hexlookup[(int)current];
            /* swap the hexs */
            if (len % 2 == 0)
            {
                tmp = *ch;
                *ch = *(ch - 1);
                *(ch - 1) = tmp;
            }
            ++ch;
        }
    }
    *ch = '\0'; /* null char */
    return outStr;
}

/* resultFileName have to be allocated with enough memory to hold the filename with extension */
char *createFileNameWithExtension(char *filename, char *extension)
{
    char *ch;
    char *resultedFileName;
    /* guard */
    if (extension == NULL || filename == NULL)
        return NULL;

    resultedFileName = (char *)malloc(FILENAME_MAX);
    ch = filename;
    /* remove the extension */
    while (*ch != '\0')
    {
        if (*ch == '.')
        {
            *ch = '\0';
        }
        ch++;
    }

    sprintf(resultedFileName, "%s.%s", filename, extension);
    return resultedFileName;
}
