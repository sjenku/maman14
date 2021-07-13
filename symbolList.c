
#include <stdlib.h>
#include <stdio.h>
#include "symbolList.h"
#include "tools.h"

int addSymbol(symbolsList *symbolList, char *name, int adderss)
{
    /*Wrong Input*/
    logger("symbolList == NULL");
    if (symbolList == NULL)
    {
        logger("FAILURE");
        return FAILURE;
    }
    /*Empty Head of Linked List*/
    else if (symbolList->head == NULL)
    {
        /*Create symbol node*/
        logger("Create symbol node");
        symbolNode *sNode = (symbolNode *)malloc(sizeof(symbolNode));

        /*Insert Values of Adress and name*/
        logger("Insert Values of Adress and name");
        sNode->adrress = adderss;
        sNode->name = name;

        /*Insert the new symbol to head of the list*/
        logger("Insert the new symbol to head of the list");
        symbolList->head = sNode;

        return SUCCESS;
    }
    else
    {
        logger("Init tmp");
        /*Set tmp to point to the head of the list*/
        symbolNode *tmp = symbolList->head;

        /*Iterate to the last Node*/
        logger("Iterate list");
        while (tmp->next)
        {
            logger("iterate next");
            tmp = tmp->next;
        }

        /*Create new symbol */
        logger("Create new symbol");
        symbolNode *sNode = (symbolNode *)malloc(sizeof(symbolNode));
        sNode->adrress = adderss;
        sNode->name = name;

        /*Insert the new symbol's node to the end of the list */
        tmp->next = sNode;
    }
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
            printf("[Symbol]=>[Name]:%s,[Address]:%d\n", tmp->name, tmp->adrress);
            tmp = tmp->next;
        }
    }
}
