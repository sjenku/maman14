
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
        logger(L, "Create symbol node");
        symbolNode *sNode = (symbolNode *)malloc(sizeof(symbolNode));

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
        logger(L, "Init tmp");
        /*Set tmp to point to the head of the list*/
        symbolNode *tmp = symbolList->head;

        /*Iterate to the last Node*/
        logger(L, "Iterate list");
        while (tmp->next)
        {
            logger(L, "iterate next");
            tmp = tmp->next;
        }

        /*Create new symbol */
        logger(L, "Create new symbol");
        symbolNode *sNode = (symbolNode *)malloc(sizeof(symbolNode));
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
