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
int deleteFirstOperetion(operetionSeg *seg);

/* Public */
operetionSeg *initOperetionSegment()
{
    operetionSeg *seg;
    seg = (operetionSeg *)malloc(sizeof(operetionSeg));
    seg->IC = 100;
    seg->head_p = NULL;
    return seg;
}

int isValidOperation(const char *str)
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
    if (seg == NULL || operetionName == NULL || value == NULL)
        return FAILURE;

    /* creating new OperetionNode for inserting it to list of operetionSegment */
    newNode = (operetionNode *)malloc(sizeof(operetionNode));

    /* handle copy of operetion name with null char */
    oprNameLength = strlen(operetionName);
    newNode->name = (char *)malloc(oprNameLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->name, operetionName);
    *(newNode->name + oprNameLength) = '\0';

    /* handle insertion of value param */
    valLength = strlen(value);
    newNode->value = (char *)malloc(valLength + 1);
    strcpy(newNode->value, value);
    *(newNode->value + valLength) = '\0';

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

void printOperetionsSeg(operetionSeg *seg)
{
    operetionNode *tmpNode;
    if (seg != NULL && seg->head_p != NULL)
    {
        tmpNode = seg->head_p;
        while (tmpNode != NULL)
        {
            logger(I, "[Name]:%s,[Value]:%s", tmpNode->name, tmpNode->value);
            tmpNode = tmpNode->next;
        }
    }
}

int deleteFirstOperetion(operetionSeg *seg)
{
    //TODO:Complete
}
