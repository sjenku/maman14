#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/dataSegment.h"
#include "headers/tools.h"
#include "headers/stringSeperator.h"
#include "headers/objectCreator.h"

#define ERR_ASCIZ_1 -400
#define ERR_ASCIZ_2 -401

#define ERR_DBDHDW_1 -501
#define ERR_DBDHDW_2 -502
#define ERR_DBDHDW_3 -503
#define ERR_DBDHDW_4 -504
#define ERR_DBDHDW_5 -505
#define ERR_DBDHDW_6 -506
#define ERR_DBDHDW_7 -507
#define ERR_DBDHDW_8 -508
#define ERR_DIRECTIVE_1 -601

static char *directiveWords[TOTAL_DIRECTIVE_WORDS] = {
    ASCIZ, DB, DH, DW};

/* private */
int removeFirstDirective(dataSeg *seg);
int maxValueNumber(const char *directiveType, int positive);

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

char *directiveErrorReason(int errorStatus)
{
    switch (errorStatus)
    {
    case ERR_ASCIZ_1:
        return "the value for directive .asciz should start with quotation marks";
    case ERR_ASCIZ_2:
        return "the value have to end with quatation marks";
    case ERR_DBDHDW_1:
        return "each value should be seperated with comma";
    case ERR_DBDHDW_2:
        return "can't declare 0 values";
    case ERR_DBDHDW_3:
        return "wrong input of number sign '+' or '-'";
    case ERR_DBDHDW_4:
        return "wrong input of space in value";
    case ERR_DBDHDW_5:
        return "wrong input of number in value";
    case ERR_DBDHDW_7:
        return "wrong chars for val";
    case ERR_DBDHDW_8:
        return "out of bounderies of max value allowed(positive or negative)";
    case ERR_DIRECTIVE_1:
        return "can't be empty value";
    default:
        return "undefined";
    }
}

int isValidDirectiveValuesDbDhDw(const char *directiveType, char *str)
{
    seperator *sep;
    char *val;
    char *ch;
    int numberOfValues;
    int status_response, valueNumber;
    int allowedNumberSign, allowedSpace, allowedNumber, lastWasNumber;
    int i;
    /* create seperator to seperate the value with comma */
    sep = initSeprator();
    status_response = appendStringWithComma(sep, str);

    /* when sepereting with comma it's checking also for correctenss of commas */
    if (status_response == FAILURE)
    {
        destroySeperator(sep);
        return ERR_DBDHDW_1;
    }

    /* set the number of values */
    numberOfValues = numberOfWords(sep);
    if (numberOfValues == 0)
    {
        destroySeperator(sep);
        return ERR_DBDHDW_2;
    }

    /* iterate threw the values */
    for (i = 0; i < numberOfValues; i++)
    {
        lastWasNumber = FALSE;
        allowedNumberSign = TRUE;
        allowedSpace = TRUE;
        allowedNumber = TRUE;
        val = getPointerToWord(sep, i + 1);
        /* iterate threw each char in val */
        for (ch = val; (*ch) != '\0'; ch++)
        {
            /* case it's a number sign */
            if ((*ch) == '-' || (*ch) == '+')
            {
                if (!allowedNumberSign)
                {
                    destroySeperator(sep);
                    return ERR_DBDHDW_3;
                }
                else
                {
                    allowedNumberSign = FALSE;
                    allowedSpace = FALSE;
                    allowedNumber = TRUE;
                }
            }
            /* case it's space */
            else if (isspace(*ch))
            {
                if (!allowedSpace)
                {
                    destroySeperator(sep);
                    return ERR_DBDHDW_4;
                }
                else if (lastWasNumber)
                {
                    allowedNumber = FALSE;
                    allowedNumberSign = FALSE;
                    allowedSpace = TRUE;
                }
            }
            /* case it's number */
            else if (isnumber(*ch))
            {
                if (!allowedNumber)
                {
                    destroySeperator(sep);
                    return ERR_DBDHDW_5;
                }
                else
                {
                    allowedNumber = TRUE;
                    allowedNumberSign = FALSE;
                    allowedSpace = TRUE;
                    lastWasNumber = TRUE;
                }
            }
            /* wrong char for val */
            else
            {
                destroySeperator(sep);
                return ERR_DBDHDW_7;
            }
        }
        /* the val passed the checks that mentioned ,now check for value size */
        valueNumber = 0; /* inital value */
        valueNumber = atoi(val);
        if (valueNumber < maxValueNumber(directiveType, NEGATIVE) || valueNumber > maxValueNumber(directiveType, POSITIVE))
        {
            destroySeperator(sep);
            return ERR_DBDHDW_8;
        }
    }
    destroySeperator(sep);
    return SUCCESS;
}
/* this function give the valid max positive or negative value capable to hold by this directive type */
int maxValueNumber(const char *directiveType, int positive)
{
    int amountOfBytes;
    amountOfBytes = directiveTypeSize(directiveType);
    switch (amountOfBytes)
    {
    case 1:
        return positive ? MAX_VAL_POSITIVE_BYTE : MAX_VAL_NEGATIVE_BYTE;
        break;
    case 2:
        return positive ? MAX_VAL_POSITIVE_2_BYTE : MAX_VAL_NEGATIVE_2_BYTE;
        break;
    case 4:
        return positive ? MAX_VAL_POSITIVE_4_BYTE : MAX_VAL_NEGATIVE_4_BYTE;
        break;
    default:
        return FAILURE;
    }
}
/* this function returns number of elements if data valid ,example: '2,5,3' return 3
and return 0 if not valid , if directiveType is .asciz then it would return number of chars
plus one, for holding the null char example : "aBcd" return 5,if not valid return 0*/
int isValidDirectiveValues(const char *directiveType, char *str)
{
    char *ch;
    int allowedComma, allowedNumber, allowedSpace, allowedSign;
    int numOfDataElements, prevCharNumber;
    int allowedApostrophes;

    /* set initial values for flags */
    allowedComma = prevCharNumber = FALSE;
    allowedNumber = allowedSpace = allowedSign = allowedApostrophes = TRUE;
    if (directiveType == NULL)
        return FAILURE;
    if (str == NULL)
        return ERR_DIRECTIVE_1;

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
            return ERR_ASCIZ_1;
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
                        return ERR_ASCIZ_2;
                    ch++;
                }
                /* it's got to the end but there is no apostrophes */
            }
            else if ((*ch) != '"')
            {
                return ERR_ASCIZ_2;
            }
        }
        numOfDataElements += 1; /* stends for null char */
        return numOfDataElements;
    }
    /* -----------handle other types (.dh,.dw,.db)-------------- */
    else
    {
        return isValidDirectiveValuesDbDhDw(directiveType, str);
    }
}
/* return the appropriate size for the value */
int sizeOfValueBytes(char *dataType, char *value)
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
    seg->DC += sizeOfValueBytes(directiveName, value);

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

int directiveTypeSize(const char *directiveName)
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
    seg->DC = 0;
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

directiveNode *getPointToDirectiveNode(dataSeg *seg, int index)
{
    /* variables */
    directiveNode *tmpNode;
    int i;

    /* guard */
    if (seg == NULL || seg->head_p == NULL)
        return NULL;

    /* set tmpNode to point on the begining of the saved directives words */
    tmpNode = seg->head_p;

    /* iterate till the directive word in the particular index , if the index
        is greater then total saved directives, then tmpNode would be NULL */
    for (i = 0; i < index && tmpNode != NULL; i++)
    {
        tmpNode = tmpNode->next;
    }

    return tmpNode;
}

/* value - is a value in format char* that inserted as is 
codedString - will hold the coded to binary value param, it should hold enough memory
for each value seperated by comma and according to directiveType,
example: if directiveType .db then should hold sizeof numberOfValue * (SIZE_BYTE + 1),the +1 stends for holding '\n' or '\0'*/
int directiveDbDhDwToCode(objList *objL, char *directiveType, char *value)
{
    /* variables */
    char *tmpCodedString;
    int val, bitsSize;
    int numberOfValues, i;
    seperator *sep; /* sep will hold the inviduals values gotten from value param */
    /* guard */
    if (directiveType == NULL || value == NULL)
        return FAILURE;

    /* init seperetor and append value param to seperate to vals */
    sep = initSeprator();
    appendStringWithComma(sep, value);

    /* get the total number of values in value param */
    numberOfValues = numberOfWords(sep);

    /* allocate memory for holding tmpCodedString for each val */
    bitsSize = (directiveTypeSize(directiveType) * SIZE_BYTE);
    tmpCodedString = (char *)malloc(bitsSize + 1); /* +1 stends for holding '\0' */
    for (i = 1; i <= numberOfValues; i++)
    {
        /* get the val as int */
        val = atoi(getPointerToWord(sep, i));
        /* code to binary */
        numberToBinary(val, bitsSize, &tmpCodedString);
        insertBinaryToObj(objL, tmpCodedString);
    }
    /* free memory */
    free(tmpCodedString);
    destroySeperator(sep);
    return SUCCESS;
}

int directiveAscizToCode(objList *objL, char *value)
{
    char *ch;
    char *byteCodedString;

    /* guard */
    if (value == NULL)
        return FAILURE;
    /* set ch to point on the begining of the value */
    ch = value;
    /* ignore the space in the begining */
    while (isspace(*ch))
        ch++;
    /* ignore the -> " */
    ch++;
    /* byteCodedString for holding tmp value of coded string for 1 char from the value */
    byteCodedString = (char *)malloc(SIZE_BYTE + 1);
    while ((*ch) != '"')
    {
        numberToBinary(*ch, SIZE_BYTE, &byteCodedString);
        insertBinaryToObj(objL, byteCodedString);
        /* move to the next char */
        ch++;
    }
    /* also code to binary the null char */
    numberToBinary('\0', SIZE_BYTE, &byteCodedString);
    insertBinaryToObj(objL, byteCodedString);
    /* free memory */
    free(byteCodedString);
    return SUCCESS;
}

char *dataToCode(dataSeg *seg, int index)
{
    directiveNode *dataNode;
    /* guard */
    if (seg == NULL || seg->head_p == NULL)
        return NULL;

    /* get the pointer to the saved directive word */
    dataNode = getPointToDirectiveNode(seg, index);
    /* guard */
    if (dataNode == NULL)
        return NULL;

    return NULL;
}
