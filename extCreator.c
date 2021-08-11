#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/extCreator.h"
#include "headers/tools.h"

/* private */
int removeFirstExternal(extList *extL);

int insertExtTo(extList *extL, char *name, int address)
{
    /* variables */
    extNode *newNode;
    extNode *tmpNode;
    int nameLength;

    /* checking if the params valid */
    if (extL == NULL || name == NULL)
        return FAILURE;

    /* creating new extNode for inserting it to list of extList */
    newNode = (extNode *)malloc(sizeof(extNode));

    /* handle copy of external symbol name with null char */
    nameLength = strlen(name);
    newNode->name = (char *)malloc(nameLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->name, name);
    *(newNode->name + nameLength) = '\0';

    /* handle insertion of address */
    newNode->address = address;

    /* set next pointer */
    newNode->next = NULL;

    /* insert First Element */
    if (extL->head_p == NULL)
    {
        extL->head_p = newNode;
    }
    else
    {
        tmpNode = extL->head_p;
        /* iterate to the last element */
        while (tmpNode->next != NULL)
        {
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
    }
    return SUCCESS;
}
extList *initExtList()
{
    extList *extL;
    extL = (extList *)malloc(sizeof(extList));
    extL->head_p = NULL;
    return extL;
}
extList *getExtList()
{
    static extList *extL;
    if (extL == NULL)
        extL = initExtList();
    return extL;
}
int createExtFileFrom(extList *extL, char *filename)
{
    /* variables */
    FILE *fileExt;
    char *fname;
    extNode *tmpNode;

    /* guard */
    if (extL == NULL || extL->head_p == NULL || filename == NULL)
        return FAILURE;

    /* creating file*/
    fname = createFileNameWithExtension(filename, "ext");
    if (fname == NULL)
        return FAILURE;

    fileExt = fopen(fname, "w");
    if (fileExt == NULL)
    {
        free(fname);
        return FAILURE;
    }

    /* iterate threw the list of saved externals symbols and put to file */
    tmpNode = extL->head_p;
    while (tmpNode != NULL)
    {
        fprintf(fileExt, "%s 0%d\n", tmpNode->name, tmpNode->address);
        tmpNode = tmpNode->next;
    }
    free(fname);
    return SUCCESS;
}
int destroyExternalsList(extList *extL)
{
    if (extL == NULL)
        return FAILURE;
    removeAllExternalsFrom(extL);
    free(extL);
    return SUCCESS;
}
int removeFirstExternal(extList *extL)
{
    extNode *temp;
    /*checking if queue isn't empty*/
    if (extL->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = extL->head_p;
    /*move the head to the next element*/
    extL->head_p = extL->head_p->next;

    /*free memory*/
    free(temp->name);
    free(temp);
    return SUCCESS;
}

void printExternals(extList *extL)
{
    extNode *tmpNode;
    if (extL != NULL && extL->head_p != NULL)
    {
        tmpNode = extL->head_p;
        while (tmpNode != NULL)
        {
            logger(I, "external adress=> %d,name =>%s", tmpNode->address, tmpNode->name);
            tmpNode = tmpNode->next;
        }
    }
}

int removeAllExternalsFrom(extList *extL)
{
    if (extL == NULL)
        return FAILURE;

    while (removeFirstExternal(extL))
        ;
    return SUCCESS;
}
