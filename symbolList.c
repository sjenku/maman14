
#include <stdlib.h>
#include <stdio.h>
#include "headers/symbolList.h"
#include "headers/tools.h"

int addSymbol(symbolsList *symbolList, char *name, int adderss)
{
    /*Wrong Input*/
    logger(L, "symbolList == NULL");
    if (symbolList == NULL)
    {
        logger(L, "FAILURE");
        return FAILURE;
    }
    /*Empty Head of Linked List*/
    else if (symbolList->head == NULL)
    {
        /*Create symbol node*/
        symbolNode *sNode;
        logger(L, "Create symbol node");
        sNode = (symbolNode *)malloc(sizeof(symbolNode));
        /*Insert Values of Adress and name*/
        logger(L, "Insert Values of Adress and name");
        sNode->adrress = adderss;
        sNode->name = name;

        /*Insert the new symbol to head of the list*/
        logger(L, "Insert the new symbol to head of the list");
        symbolList->head = sNode;

        return SUCCESS;
    }
    else
    {
        symbolNode *tmp;
        symbolNode *sNode;

        logger(L, "Init tmp");
        tmp = symbolList->head;

        /*Iterate to the last Node*/
        logger(L, "Iterate list");
        while (tmp->next)
        {
            logger(L, "iterate next");
            tmp = tmp->next;
        }
        /*Create new symbol */
        logger(L, "Create new symbol");
        sNode = (symbolNode *)malloc(sizeof(symbolNode));
        sNode->adrress = adderss;
        sNode->name = name;

        /*Insert the new symbol's node to the end of the list */
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
        while (tmp != NULL && tmp->next != NULL)
        {
            logger(I, "[Symbol]=>[Name]:%s,[Address]:%d\n", tmp->name, tmp->adrress);
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
