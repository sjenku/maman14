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

int isValidDirectiveValues(char *str)
{
    char *ch;
    int commaFlag;

    /* set to true to handle case the first char is comma that not allowed */
    commaFlag = TRUE;
    for (ch = str; (*ch) != '\0'; ch++)
    {
        if (!isspace((*ch)))
        {
            /* if it's a comma and there is already comma before , return failure */
            if (*ch == ',')
            {
                if (commaFlag == TRUE)
                    return FAILURE;
                /* case it's a comma but before wasn't one */
                else
                    commaFlag = TRUE;
            }
            else
            {
                /* set to false allowing next char to be a comma */
                commaFlag = FALSE;
            }
        }
    }
    /* check if the last char is comma */
    if (commaFlag == TRUE)
        return FAILURE;
    else
        return SUCCESS;
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

    /* creating new OperetionNode for inserting it to list of operetionSegment */
    newNode = (directiveNode *)malloc(sizeof(directiveNode));

    /* handle copy of operetion name with null char */
    directiveNameLength = strlen(directiveName);
    newNode->name = (char *)malloc(directiveNameLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->name, directiveName);
    *(newNode->name + directiveNameLength) = '\0';

    /* handle insertion of value param */
    valLength = strlen(value);
    newNode->value = (char *)malloc(valLength + 1);
    strcpy(newNode->value, value);
    *(newNode->value + valLength) = '\0';

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
