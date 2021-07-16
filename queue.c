#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/queue.h"

//TODO: free all elements
int enqueue(queue *queue, char *word)
{
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

/*This Function enqueue each word seperating it if space accure*/
void enqueueWordsFromString(queue *queue, char *str)
{
    char *ch; //used to iterate threw string and look on each char in it.
    int i;    //index of each char
    int charCounter = 0;
    int totalChars = strlen(str);
    //Iterats threw all the characters in the str
    for (i = 0, ch = str; i < totalChars + 1; i++, ch++) //+1 stends for '\0'
    {
        //checking if there is a space or end of string
        if ((*ch) == ' ' || (*ch) == '\0')
        {
            //charCounter != 0 means that previuos chars isn't space
            if (charCounter != 0)
            {
                //Creating new word buffer, note: this memory will be free in dequeue method.
                char *newWord = (char *)malloc(charCounter + 1);
                //copy the word from the str with relative indexes
                strncpy(newWord, str + i - charCounter, charCounter);
                enqueue(queue, newWord);
                logger(L, "Word is fetched is => %s", newWord);
                //after finish adding the word , zero the char counter
                charCounter = 0;
            }
        }
        else
        {
            //there is not a space char so start count amount of chars in this word
            charCounter++;
        }
    }
}
