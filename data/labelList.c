
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/labelList.h"
#include "../headers/tools.h"

int addLabel(labelsList *labelList, char *name, int adderss, char *labelAttribute) /*TODO:Optemize in one block make new node*/
{
    labelNode *sNode;
    labelNode *tmp;
    /*Wrong Input*/
    if (labelList == NULL)
    {
        logger(L, "FAILURE");
        return FAILURE;
    }
    /*Create label node*/
    logger(L, "Create label node");
    sNode = (labelNode *)malloc(sizeof(labelNode));
    /*Insert Values of Adress and name*/
    logger(L, "Insert Values of Adress and name");
    sNode->adrress = adderss;
    sNode->name = (char *)malloc(sizeof(name) + 1); /*NOTE:Will be free in 'DestroylabelList' method*/
    strcpy(sNode->name, name);
    sNode->attribute = (char *)malloc(sizeof(labelAttribute) + 1);
    strcpy(sNode->attribute, labelAttribute);
    sNode->next = NULL;

    /*Empty Head of Linked List*/
    if (labelList->head == NULL)
    {
        /*Insert the new label to head of the list*/
        logger(L, "Insert the new label to head of the list");
        labelList->head = sNode;

        return SUCCESS;
    }
    else
    {
        logger(L, "Init tmp");
        tmp = labelList->head;
        logger(L, "tmp => %s", tmp->name);

        /*Iterate to the last Node*/
        logger(L, "Iterate list");
        while (tmp->next)
        {
            logger(L, "iterate next");
            tmp = tmp->next;
        }
        /*Insert the new label's node to the end of the list */
        logger(I, "insert the next label to the list => %s", sNode->name);
        tmp->next = sNode;
        return SUCCESS;
    }
    return FAILURE;
}

int labelExist(labelsList *list, char *name)
{
    labelNode *tmp;
    if (list == NULL)
        return FAILURE;

    tmp = list->head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name) == 0)
            return SUCCESS;
        else
            tmp = tmp->next;
    }
    return FAILURE;
}

void printLabelsFrom(labelNode *head)
{
    if (head == NULL)
        return;
    else
    {
        /*Iterate threw the list begining from the node been givin in the param*/
        labelNode *tmp = head;
        while (tmp != NULL)
        {
            logger(D, "[label]=>[Name]:%s,[Address]:%d,[ATTRIBUTE]:%s", tmp->name, tmp->adrress, tmp->attribute);
            tmp = tmp->next;
        }
    }
}

labelsList *initLabelsList()
{
    labelsList *newList;
    newList = (labelsList *)malloc(sizeof(labelsList));
    if (newList == NULL)
        return NULL;

    newList->head = NULL;
    return newList;
}

/*Remove all the elements and Release all the memory*/
void destoryLabelList(labelsList *labelsList)
{
    labelNode *tmp;
    if (labelsList == NULL)
        return;

    tmp = labelsList->head;
    while (tmp != NULL)
    {
        if (tmp->name != NULL)
            free(tmp->name);
        if (tmp->attribute != NULL)
            free(tmp->attribute);

        labelsList->head = labelsList->head->next;
        free(tmp);
        tmp = labelsList->head;
    }
    free(labelsList);
}
