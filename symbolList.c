
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/symbolList.h"
#include "headers/tools.h"

int addSymbol(symbolsList *symbolList, char *name, int adderss) /*TODO:Optemize in one block make new node*/
{
    symbolNode *sNode;
    symbolNode *tmp;
    /*Wrong Input*/
    if (symbolList == NULL)
    {
        logger(L, "FAILURE");
        return FAILURE;
    }
    /*Create symbol node*/
    logger(L, "Create symbol node");
    sNode = (symbolNode *)malloc(sizeof(symbolNode));
    /*Insert Values of Adress and name*/
    logger(L, "Insert Values of Adress and name");
    sNode->adrress = adderss;
    sNode->name = (char *)malloc(sizeof(name)); /*NOTE:Will be free in 'DestroySymbolList' method*/
    strcpy(sNode->name, name);
    sNode->next = NULL;

    /*Empty Head of Linked List*/
    if (symbolList->head == NULL)
    {
        /*Insert the new symbol to head of the list*/
        logger(L, "Insert the new symbol to head of the list");
        symbolList->head = sNode;

        return SUCCESS;
    }
    else
    {
        logger(L, "Init tmp");
        tmp = symbolList->head;
        logger(L, "tmp => %s", tmp->name);

        /*Iterate to the last Node*/
        logger(L, "Iterate list");
        while (tmp->next)
        {
            logger(L, "iterate next");
            tmp = tmp->next;
        }
        /*Insert the new symbol's node to the end of the list */
        logger(L, "insert the next symbol to the list => %s", sNode->name);
        tmp->next = sNode;
        return SUCCESS;
    }
    return FAILURE;
}

void printSymbolsFrom(symbolNode *head)
{
    if (head == NULL)
        return;
    else
    {
        /*Iterate threw the list begining from the node been givin in the param*/
        symbolNode *tmp = head;
        while (tmp != NULL)
        {
            logger(I, "[Symbol]=>[Name]:%s,[Address]:%d", tmp->name, tmp->adrress);
            tmp = tmp->next;
        }
    }
}

symbolsList *initSymbolsList()
{
    symbolsList *newList;
    newList = (symbolsList *)malloc(sizeof(symbolsList));
    if (newList == NULL)
        return NULL;

    newList->head = NULL;
    return newList;
}

/*Remove all the elements and Release all the memory*/
void destorySymbolList(symbolsList *symbolsList)
{
    symbolNode *tmp;
    if (symbolsList == NULL || symbolsList->head == NULL)
        return;

    tmp = symbolsList->head;
    while (tmp != NULL)
    {
        if (tmp->name != NULL)
            free(tmp->name);

        symbolsList->head = symbolsList->head->next;
        free(tmp);
        tmp = symbolsList->head;
    }
    free(symbolsList);
}
