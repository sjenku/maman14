#include <string.h>
#include <stdlib.h>
#include "../headers/tools.h"
#include "../headers/dataGuidance.h"
#include "../headers/queue.h"

static char *dataGuidance[TOTAL_DATA_GUIDANCE] = {
    EMPTY, ASCIZ, DB, DW, DH};

int isDataGuidanceWord(const char *word)
{
    int i;
    int length = TOTAL_DATA_GUIDANCE;

    for (i = 1; i < length; i++)
    {
        if (strcmp(dataGuidance[i], word) == 0)
            return i;
    }
    return FAILURE;
}

/* returns the size for memory needed for each element of the data type 
it's returns 0 if there is wrong data word*/
int sizeOfGuidanceDataType(const char *word)
{
    int type;
    type = isDataGuidanceWord(word);
    switch (type)
    {
    case 1:
        return SIZE_ASCIZ;
    case 2:
        return SIZE_DB;
    case 3:
        return SIZE_DW;
    case 4:
        return SIZE_DH;
    default:
        break;
    }
    return FAILURE;
}

/* this function returns number of elements if data valid ,example: '2,5,3' return 3
and return 0 if not valid */
int isValidData(const char *dataType, char *word)
{
    char *ch;
    int allowedComma, allowedNumber, allowedSpace, allowedSign;
    int numOfDataElements, prevCharNumber;
    int allowedApostrophes;
    allowedComma = prevCharNumber = FALSE;
    allowedNumber = allowedSpace = allowedSign = allowedApostrophes = TRUE;

    /* -------------handle case if it's ASCIZ type------------------ */
    if (strcmp(dataType, ASCIZ) == 0)
    {
        numOfDataElements = 0;
        ch = word;
        /* ignore space till first char */
        while ((*ch) == ' ')
            ch++;
        /* check if the first char is " */
        if ((*ch) != '"')
        {
            return FAILURE;
        }
        else
        {
            ch++;
            /* iterate remaining characters between the apostrophes */
            while ((*ch) != '"' && (*ch) != '\0')
            {
                numOfDataElements++;
                ch++;
            }
            /* check if the last char is apostrophes and there is not more chars after it */
            if ((*ch) == '"' && *(ch + 1) != '\0')
            {
                ch++;
                while (*ch != '\0')
                {
                    if ((*ch) != ' ' && (*ch) != '\t')
                        return FAILURE;
                    ch++;
                }
            }
        }
        numOfDataElements += 1; /* stends for null char */
        return numOfDataElements;
    }

    /* -----------handle other types (.dh,.dw,.db)-------------- */
    numOfDataElements = 1;
    if (word == NULL || strcmp(word, "") == 0)
        return FAILURE;

    ch = word;
    while ((*ch) != '\0')
    {
        /* Space */
        if (((*ch) == ' ' || (*ch) == '\t'))
        {

            if (prevCharNumber)
                allowedNumber = FALSE;
        }
        /* Comma */
        else if ((*ch) == ',' && allowedComma)
        {

            numOfDataElements++;
            allowedComma = FALSE;
            allowedNumber = TRUE;
            prevCharNumber = FALSE;
            allowedSign = TRUE;
        }
        /* Number */
        else if ((*ch) >= '0' && (*ch) <= '9' && allowedNumber)
        {
            allowedComma = TRUE;
            prevCharNumber = TRUE;
            allowedSign = FALSE;
        }
        /* Sing */
        else if (((*ch) == '-' || (*ch == '+')) && allowedSign)
        {
            allowedSign = FALSE;
            allowedNumber = TRUE;
            allowedComma = FALSE;
            allowedSpace = FALSE;
        }
        else
        {
            return FAILURE;
        }
        ch++;
    }

    /*TODO: handle in for loop with strlen to insert it up*/
    /*check if the last char is comma or sign*/
    if ((*(ch - 1) == ',') || (*(ch - 1) == '-') || (*(ch - 1) == '+'))
        return FAILURE;

    return numOfDataElements;
}

/* iterate threw the data and checks if it's all numbers 
return -1 if it's not only numbers
and integer specify the amount of numbers*/
int isOnlyNumbers(char *data)
{
    int size;
    char *ch;
    size = 0;

    for (ch = data; (*ch) != '\0'; ch++)
    {
        if ((*ch) < '0' || (*ch) > '9')
            return -1;
        else
            size++;
    }
    return size;
}
