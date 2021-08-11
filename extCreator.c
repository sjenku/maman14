#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/extCreator.h"
#include "headers/tools.h"

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
    char fName[MAX_NAMEFILE_CHARS];
    extNode *tmpNode;

    /* guard */
    if (extL == NULL || extL->head_p == NULL || filename == NULL)
        return FAILURE;

    /* creating file*/
    sprintf(fName, "%s%s", filename, ".ext");
    fileExt = fopen(fName, "w");
    if (fileExt == NULL)
    {
        return FAILURE;
    }

    /* iterate threw the list of saved externals symbols and put to file */
    tmpNode = extL->head_p;
    while (tmpNode != NULL)
    {
        fprintf(fileExt, "%s 0%d\n", tmpNode->name, tmpNode->address);
        tmpNode = tmpNode->next;
    }
    return SUCCESS;
}
