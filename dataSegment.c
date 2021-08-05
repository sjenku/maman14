#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/dataSegment.h"
#include "headers/tools.h"

static char *directiveWords[TOTAL_DIRECTIVE_WORDS] = {
    ASCIZ, DB, DH, DW};

/* private */
int directiveTypeSize(char *directiveName);
int removeFirstDirective(dataSeg *seg);
int removeAllDataFrom(dataSeg *seg);

/* public */

dataSeg *initDataSegment()
{
    dataSeg *seg;
    seg = (dataSeg *)malloc(sizeof(dataSeg));
    seg->DC = 0;
    seg->head_p = NULL;
    return seg;
}

int isValidDirectiveName(const char *str)
{
    int i;
    for (i = 0; i < TOTAL_DIRECTIVE_WORDS; i++)
    {
        if (strcmp(directiveWords[i], str) == 0)
            return SUCCESS;
    }
    return FAILURE;
}

/* this function returns number of elements if data valid ,example: '2,5,3' return 3
and return 0 if not valid */
int isValidDirectiveValues(const char *directiveType, char *str)
{
    char *ch;
    int allowedComma, allowedNumber, allowedSpace, allowedSign;
    int numOfDataElements, prevCharNumber;
    int allowedApostrophes;

    /* set initial values for flags */
    allowedComma = prevCharNumber = FALSE;
    allowedNumber = allowedSpace = allowedSign = allowedApostrophes = TRUE;

    /* -------------handle case if it's ASCIZ type------------------ */
    if (strcmp(directiveType, ASCIZ) == 0)
    {
        numOfDataElements = 0;
        ch = str;
        /* ignore space till first char */
        while (isspace(*ch))
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
                    if (!isspace(*ch))
                        return FAILURE;
                    ch++;
                }
            }
            /* check case  the last char apostrophes and no more char after it */
            else if (*ch != '"')
            {
                return FAILURE;
            }
        }
        numOfDataElements += 1; /* stends for null char */
        return numOfDataElements;
    }

    /* -----------handle other types (.dh,.dw,.db)-------------- */
    numOfDataElements = 1;
    if (str == NULL || strcmp(str, "") == 0)
        return FAILURE;

    ch = str;
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

/* return the appropriate size for the value */
int sizeOfValue(char *dataType, char *value)
{
    int numOfElements;
    numOfElements = isValidDirectiveValues(dataType, value);
    return directiveTypeSize(dataType) * numOfElements;
}

dataSeg *getDataSegment()
{
    static dataSeg *seg;
    if (seg == NULL)
        seg = initDataSegment();
    return seg;
}

int isEntry(char *str)
{
    return (strcmp(str, ".entry") == 0) ? SUCCESS : FAILURE;
}

int isExternal(char *str)
{
    return (strcmp(str, ".extern") == 0) ? SUCCESS : FAILURE;
}

int insertDirectiveTo(dataSeg *seg, char *directiveName, char *value)
{
    /* variables */
    directiveNode *newNode;
    directiveNode *tmpNode;
    int directiveNameLength, valLength;

    /* checking if the params valid */
    if (seg == NULL || directiveName == NULL || value == NULL)
        return FAILURE;

    /* get the value size */

    /* creating new directiveNode for inserting it to list of dataSegment */
    newNode = (directiveNode *)malloc(sizeof(directiveNode));

    /* handle copy of direvtive name with null char */
    directiveNameLength = strlen(directiveName);
    newNode->name = (char *)malloc(directiveNameLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->name, directiveName);
    *(newNode->name + directiveNameLength) = '\0';

    /* handle insertion of value param */
    valLength = strlen(value);
    newNode->value = (char *)malloc(valLength + 1);
    strcpy(newNode->value, value);
    *(newNode->value + valLength) = '\0';

    /* handle insertion of address */
    newNode->address = seg->DC;
    seg->DC += sizeOfValue(directiveName, value);

    /* set next pointer */
    newNode->next = NULL;

    /* insert First Element */
    if (seg->head_p == NULL)
    {
        seg->head_p = newNode;
    }
    else
    {
        tmpNode = seg->head_p;
        /* iterate to the last element */
        while (tmpNode->next != NULL)
        {
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
    }
    return SUCCESS;
}

int directiveTypeSize(char *directiveName)
{
    if (strcmp(directiveName, ASCIZ) == 0)
        return 1;
    else if (strcmp(directiveName, DB) == 0)
        return 1;
    else if (strcmp(directiveName, DH) == 0)
        return 2;
    else if (strcmp(directiveName, DW) == 0)
        return 4;
    else
        return FAILURE;
}

void printDataSeg(dataSeg *seg)
{
    directiveNode *tmpNode;
    if (seg != NULL && seg->head_p != NULL)
    {
        tmpNode = seg->head_p;
        while (tmpNode != NULL)
        {
            logger(I, "[Name]:%s,[Value]:%s,[Address]:%d", tmpNode->name, tmpNode->value, tmpNode->address);
            tmpNode = tmpNode->next;
        }
    }
}

int removeFirstDirective(dataSeg *seg)
{
    directiveNode *temp;
    /*checking if queue isn't empty*/
    if (seg->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = seg->head_p;
    /*move the head to the next element*/
    seg->head_p = seg->head_p->next;

    /*free memory*/
    free(temp->value);
    free(temp->name);
    free(temp);
    return SUCCESS;
}

int removeAllDataFrom(dataSeg *seg)
{
    if (seg == NULL)
        return FAILURE;

    while (removeFirstDirective(seg))
        ;
    return SUCCESS;
}

int destroyDataSeg(dataSeg *seg)
{
    if (seg == NULL)
        return FAILURE;
    removeAllDataFrom(seg);
    free(seg);
    return SUCCESS;
}

int moveAddressDataSeg(dataSeg *seg, int ICF)
{
    directiveNode *tmpNode;
    if ((seg == NULL) || (seg->head_p == NULL))
        return FAILURE;
    else
    {
        tmpNode = seg->head_p;
        while (tmpNode != NULL)
        {
            tmpNode->address += ICF;
            tmpNode = tmpNode->next;
        }
        return SUCCESS;
    }
}
