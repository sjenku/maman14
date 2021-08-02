#include <string.h>
#include <stdlib.h>
#include "headers/operetionSegment.h"
#include "headers/tools.h"

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

/* Public */
char *toMachineCode(char *operetionName)
{
    /* retrieve the info about this kind of operetion */
    operetionInfo *oprInfo;
    oprInfo = getOperetionInfo(operetionName);
    switch (oprInfo->type)
    {
    case 'R':
        return "It's an R command";
    case 'J':
        return "It's an J command";
    case 'I':
        return "It's an I command";
    default:
        return "no type";
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
