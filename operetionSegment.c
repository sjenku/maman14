#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/operetionSegment.h"
#include "headers/tools.h"
#include "headers/stringSeperator.h"

static operetionInfo validOperations[] = {
    {"add", 'R', 1, 0},
    {"sub", 'R', 2, 0},
    {"and", 'R', 3, 0},
    {"or", 'R', 4, 0},
    {"nor", 'R', 5, 0},
    {"move", 'R', 1, 1},
    {"mvhi", 'R', 2, 1},
    {"mvlo", 'R', 3, 1},
    {"addi", 'I', -1, 10},
    {"subi", 'I', -1, 11},
    {"andi", 'I', -1, 12},
    {"ori", 'I', -1, 13},
    {"nori", 'I', -1, 14},
    {"bne", 'I', -1, 15},
    {"beq", 'I', -1, 16},
    {"blt", 'I', -1, 17},
    {"bgt", 'I', -1, 18},
    {"lb", 'I', -1, 19},
    {"sb", 'I', -1, 20},
    {"lw", 'I', -1, 21},
    {"sw", 'I', -1, 22},
    {"lh", 'I', -1, 23},
    {"sh", 'I', -1, 24},
    {"jmp", 'J', -1, 30},
    {"la", 'J', -1, 31},
    {"call", 'J', -1, 32},
    {"stop", 'J', -1, 63}};

/* Private */
int totalOperations();
int removeFirstOperetion(operetionSeg *seg);
int removeAllOperetionsFrom(operetionSeg *seg);
operetionInfo *getOperetionInfo(char *operetionName);
int isRegister(char *str);

/* Public */
int numberToBinary(int numValue, int sizeOfBits, char **codedString)
{
    int k, indexString, i;
    /* check valid param and that codedString have enough memory to hold the coded num */
    if (codedString == NULL)
        return FAILURE;
    logger(I, "enterd numberToBinary");

    for (indexString = 0, i = sizeOfBits - 1; i >= 0; i--, indexString++)
    {
        k = numValue >> i;
        if (k & 1)
            (*codedString)[indexString] = '1';
        else
            (*codedString)[indexString] = '0';
    }
    (*codedString)[indexString + 1] = '\0';
    logger(I, "result => %s", *codedString);
    return SUCCESS;
}

int operetionRToCode(operetionR *oprR, char *codedString)
{
    /* allocating temperory memory */
    int status;
    char *emptyStr, *opcodeStr, *functStr, *rdStr, *rtStr, *rsStr;
    if (oprR == NULL)
        return FAILURE;

    emptyStr = (char *)malloc(R_CODE_EMPTY_SIZE + 1); /* +1 stends for null char */
    opcodeStr = (char *)malloc(R_CODE_OPCODE_SIZE + 1);
    functStr = (char *)malloc(R_CODE_FUNCT_SIZE + 1);
    rdStr = (char *)malloc(R_CODE_RD_SIZE + 1);
    rtStr = (char *)malloc(R_CODE_RT_SIZE + 1);
    rsStr = (char *)malloc(R_CODE_RS_SIZE + 1);

    /* code to binary each section and check if it was succesefully */
    if (numberToBinary(oprR->opcode, R_CODE_OPCODE_SIZE, &opcodeStr) &&
        numberToBinary(oprR->funct, R_CODE_FUNCT_SIZE, &functStr) &&
        numberToBinary(oprR->rd, R_CODE_RD_SIZE, &rdStr) &&
        numberToBinary(oprR->rt, R_CODE_RT_SIZE, &rtStr) &&
        numberToBinary(oprR->rs, R_CODE_RS_SIZE, &rsStr) &&
        numberToBinary(oprR->empty, R_CODE_EMPTY_SIZE, &emptyStr))
    {
        /* create the coded string */
        strcpy(codedString, opcodeStr);
        strcat(codedString, rsStr);
        strcat(codedString, rtStr);
        strcat(codedString, rdStr);
        strcat(codedString, functStr);
        strcat(codedString, emptyStr);
        strcat(codedString, "\0");

        status = SUCCESS;
    }
    else
    {
        status = FAILURE;
    }
    /* free memory */
    free(opcodeStr);
    free(rsStr);
    free(rtStr);
    free(rdStr);
    free(functStr);
    free(emptyStr);
    return status;
}

int isValidOperetionValueR(char *values)
{
    /* variables */
    seperator *sep;
    char *value;
    int i;

    /* initial */
    sep = initSeprator();

    /* seperete the values to individuals words */
    if (appendStringWithComma(sep, values))
    {
        /* check if there is 3 operands */
        if (numberOfWords(sep) != 3)
        {
            destroySeperator(sep);
            return FAILURE;
        }
        /* there is correct number of operands */
        else
        {
            /* iterate threw each of them and check if it's register*/
            for (i = 0; i < 3; i++)
            {
                value = getPointerToWord(sep, i + 1);
                if (!isRegister(value))
                {
                    destroySeperator(sep);
                    return FAILURE;
                }
            }
            destroySeperator(sep);
            return SUCCESS;
        }
    }
    destroySeperator(sep);
    return FAILURE;
}

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
            return SUCCESS;
        else
            return FAILURE;
    }
}

operetionInfo *getOperetionInfo(char *name)
{
    int i, totalOpr;
    totalOpr = totalOperations();
    if (name == NULL)
        return NULL;
    else
    {
        /* iterate to find mathcing operetion name */
        for (i = 0; i < totalOpr; i++)
        {
            if (strcmp(name, validOperations[i].name) == 0)
                return &validOperations[i];
        }
        /* not found */
        return NULL;
    }
}

operetionSeg *initOperetionSegment()
{
    operetionSeg *seg;
    seg = (operetionSeg *)malloc(sizeof(operetionSeg));
    seg->IC = 100;
    seg->head_p = NULL;
    return seg;
}

int isValidOperationName(const char *str)
{
    int i;
    int length = totalOperations();
    for (i = 0; i < length; i++)
    {
        if (strcmp(validOperations[i].name, str) == 0)
            return SUCCESS;
    }
    return FAILURE;
}
/*
int isValidOperetionValue(const char *value)
{
    int i;
    int length = totalOperations();
    for (i = 0; i < length; i++)
    {
        if (strcmp(validOperations[i].name, value) == 0)
            return SUCCESS;
    }
    return FAILURE;
}
*/
int totalOperations()
{
    return sizeof(validOperations) / sizeof(operetionInfo);
}

int insertOperetionTo(operetionSeg *seg, char *operetionName, char *value)
{
    /* variables */
    operetionNode *newNode;
    operetionNode *tmpNode;
    int oprNameLength, valLength;

    /* checking if the params valid */
    if (seg == NULL || operetionName == NULL)
        return FAILURE;

    /* creating new OperetionNode for inserting it to list of operetionSegment */
    newNode = (operetionNode *)malloc(sizeof(operetionNode));

    /* handle copy of operetion name with null char */
    oprNameLength = strlen(operetionName);
    newNode->name = (char *)malloc(oprNameLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->name, operetionName);
    *(newNode->name + oprNameLength) = '\0';

    /* handle insertion of value param */
    if (value != NULL)
    {
        valLength = strlen(value);
        newNode->value = (char *)malloc(valLength + 1);
        strcpy(newNode->value, value);
        *(newNode->value + valLength) = '\0';
    }
    else
    /* insert '\0' if value NULL */
    {
        valLength = 1;
        newNode->value = (char *)malloc(valLength);
        *(newNode->value + valLength) = '\0';
    }

    /* set next pointer */
    newNode->next = NULL;

    /* set instruction counter IC */
    newNode->address = seg->IC;
    seg->IC += IC_INCREASER;
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

/* singelton approach */
operetionSeg *getOperetionSegment()
{
    static operetionSeg *seg;
    if (seg == NULL)
        seg = initOperetionSegment();
    return seg;
}

void printOperetionsSeg(operetionSeg *seg)
{
    operetionNode *tmpNode;
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

int removeFirstOperetion(operetionSeg *seg)
{
    operetionNode *temp;
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

int removeAllOperetionsFrom(operetionSeg *seg)
{
    if (seg == NULL)
        return FAILURE;

    while (removeFirstOperetion(seg))
        ;
    return SUCCESS;
}

int destroyOperetionSeg(operetionSeg *seg)
{
    if (seg == NULL)
        return FAILURE;
    removeAllOperetionsFrom(seg);
    free(seg);
    return SUCCESS;
}
