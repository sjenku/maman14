#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/tools.h"
#include "../headers/queue.h"

/*TODO: free all elements*/
int enqueue(queue *queue, const char *word)
{
    node *newNode;
    /*WRONG INPUT*/
    if (queue == NULL)
    {
        logger(E, "passed paramater queue as NULL");
        return FAILURE;
    }

    /*Create new element for the queue*/
    newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
        return FAILURE;

    newNode->data = (char *)malloc(strlen(word) + 1);
    if (newNode->data == NULL)
        return FAILURE;

    strcpy(newNode->data, word);
    newNode->next = NULL;

    if (queue->headP == NULL)
    {
        /*Insert to the queue*/
        queue->headP = newNode;
        queue->tailP = newNode;
        return SUCCESS;
    }
    else
    {
        /*Insert to the queue*/
        queue->tailP->next = newNode;
        queue->tailP = newNode;
        return SUCCESS;
    }
    return FAILURE;
}

/*Return the size of the string that saved in the first element in the queue
(note:it's count also the null character)*/
size_t sizeDataFirstElement(queue *q)
{
    if (q == NULL || q->headP == NULL || q->headP->data == NULL)
        return 0;
    return strlen(q->headP->data);
}

void display(node *headP)
{
    node *tmp = headP;
    while (tmp != NULL)
    {
        logger(E, tmp->data);
        tmp = tmp->next;
    }
}

/*This Function enqueue each word seperating it with seperators provided accure*/
void enqueueStringSeperateWith(queue *queue, char *str, char seperator1, char seperator2, char seperator3)
{
    char *ch; /*used to iterate threw string and look on each char in it.*/
    int i;    /*index of each char*/
    int charCounter = 0;
    int totalChars = strlen(str);
    /*Iterats threw all the characters in the str*/
    for (i = 0, ch = str; i < totalChars + 1; i++, ch++) /*  +1 stends for '\0'  */
    {
        /*checking if there is a space or end of string*/
        if ((*ch) == seperator1 || (*ch) == seperator2 || (*ch) == seperator3 || (*ch) == '\0')
        {
            /*charCounter != 0 means that previuos chars isn't space*/
            if (charCounter != 0)
            {
                /*Creating new word buffer,note:the memory will be free in the dequeue method.*/
                char *newWord = (char *)malloc(charCounter + 1);
                /*copy the word from the str with relative indexes*/
                strncpy(newWord, str + i - charCounter, charCounter);
                *(newWord + charCounter) = '\0'; /*end of the word*/
                enqueue(queue, newWord);
                /*after finish adding the word , zero the char counter*/
                charCounter = 0;
                /*free memory*/
                free(newWord);
            }
        }
        else
        {
            /*there is not a space char so start count amount of chars in this word*/
            charCounter++;
        }
    }
}

/*this method dequeue element from the queue,returning 0 if there was empty queue and 1 if
the element been dequeued*/
int dequeue(queue *q)
{
    node *temp;
    /*checking if queue isn't empty*/
    if (q->headP == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = q->headP;
    /*move the head to the next element*/
    q->headP = q->headP->next;

    /*Checking if now the queue became empty then set tailP to NULL also.*/
    if (q->headP == NULL)
        q->tailP = NULL;

    /*return to the client the node been removed from the queue*/
    free(temp->data);
    free(temp);
    return SUCCESS;
}

/*this method will copy the content to the client's buffer for the data of the first element without removing it*/
int peek(queue *q, char **str)
{
    if (q->headP == NULL)
        return FAILURE;
    else
    {
        strcpy(*str, q->headP->data);
        return SUCCESS;
    }
}

/*Init queue - this function return pointer to new initialized queue*/
queue *initQueue()
{
    queue *newQueue = (queue *)malloc(sizeof(queue));
    if (newQueue == NULL)
        return NULL;

    newQueue->headP = NULL;
    newQueue->tailP = NULL;
    return newQueue;
}

/*This method dequeue all the elements from the queue*/
int dequeueAll(queue *q)
{
    if (q == NULL)
        return FAILURE;

    logger(L, "start to dequeue %p", q);
    while (dequeue(q))
    {
        logger(L, "dequeItem");
    }
    return SUCCESS;
}

/*This method should be used when finish using the queue,the main reason is to avoid memory leak*/
int destroyQueue(queue *q)
{
    /*TODO:FINISH*/
    if (q == NULL)
        return FAILURE;
    dequeueAll(q);
    free(q);
    return SUCCESS;
}

int isEmpty(queue *q)
{
    if (q == NULL)
        return SUCCESS;
    else if (q->headP == NULL)
        return SUCCESS;
    else
        return FAILURE;
}

/* return the size of data elements */
int sizeOfQueueData(queue *q)
{
    node *tmpNode;
    int size;
    size = 0;
    tmpNode = q->headP;
    while (tmpNode != NULL)
    {
        size += strlen(tmpNode->data);
        tmpNode = tmpNode->next;
    }
    return size;
}

void catToStringWithSpace(queue *q, char *str)
{
    node *tmpNode;
    tmpNode = q->headP;
    int i = 1;
    while (tmpNode != NULL)
    {
        if (i == 1)
        {
            strcpy(str, tmpNode->data);
            i++;
        }
        else
        {
            strcat(str, tmpNode->data);
        }
        strcat(str, " "); /* add space */
        tmpNode = tmpNode->next;
    }
}
