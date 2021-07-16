#include <stdlib.h>
#include <stdio.h>
#include "headers/tools.h"
#include "headers/queue.h"

//TODO: free all elements
int enqueue(queue *queue, char *word)
{
    //TODO:
    //WRONG INPUT
    if (queue == NULL)
    {
        logger(E, "passed paramater queue as NULL");
        return FAILURE;
    }

    //Create new element for the queue
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = word;
    newNode->next = NULL;
    if (queue->headP == NULL)
    {
        logger(I, "Init the first elemnt with => %s", word);
        //Insert to the queue
        queue->headP = newNode;
        queue->tailP = newNode;
        return SUCCESS;
    }
    else
    {
        logger(I, "Insert to the end of the queue new element with => %s", word);
        //Insert to the queue
        queue->tailP->next = newNode;
        queue->tailP = newNode;
        return SUCCESS;
    }

    return FAILURE;
}

void display(node *headP)
{
    node *tmp = headP;
    while (tmp != NULL)
    {
        logger(I, "Node with word => %s", tmp->data);
        tmp = tmp->next;
    }
}
