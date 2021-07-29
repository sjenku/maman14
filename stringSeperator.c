#include <stdlib.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/stringSeperator.h"

void appendString(seperator *seperator, char *str)
{
    char *ch;
    int i, charCounter;
    int totalChars;
    totalChars = strlen(str);
    /* Seperate the words */
    for (ch = str, i = 0, charCounter = 0; i < totalChars + 1; ch++, i++)
    {
        /* indicates it's a space so it's end of first word */
        if ((*ch) == ' ' || (*ch) == '\t' || (*ch) == '\0')
        {
            /*charCounter != 0 means that previuos chars isn't space*/
            if (charCounter != 0)
            {
                /*Creating new word buffer,note:the memory will be free in the dequeue method.*/
                char *newWord = (char *)malloc(charCounter + 1);
                /*copy the word from the str with relative indexes*/
                strncpy(newWord, str + i - charCounter, charCounter);
                *(newWord + charCounter) = '\0'; /*end of the word*/
                appendWord(seperator, newWord);
                /*after finish adding the word , zero the char counter*/
                charCounter = 0;
                /*free memory*/
                free(newWord);
            }
        }
        else
        {
            charCounter++;
        }
    }
}

int appendWord(seperator *seperator, char *word)
{
    seperatorNode *newNode;
    seperatorNode *node_p;
    /* Wrong Input */
    if (seperator == NULL || word == NULL)
        return FAILURE;

    /* Create New Node */
    newNode = (seperatorNode *)malloc(sizeof(newNode));
    newNode->word = (char *)malloc(strlen(word));
    newNode->next = NULL;
    strcpy(newNode->word, word);

    /* Handle First Word Inserted */
    if (seperator->head_p == NULL)
    {
        seperator->head_p = newNode;
        return SUCCESS;
    }
    /* insert next to the last node with prev word */
    else
    {
        node_p = seperator->head_p;
        while (node_p->next != NULL)
        {
            node_p = node_p->next;
        }
        node_p->next = newNode;
        return SUCCESS;
    }
    return FAILURE;
}

seperator *initSeprator()
{
    seperator *newSeperator = (seperator *)malloc(sizeof(seperator));
    if (newSeperator == NULL)
        return NULL;

    newSeperator->head_p = NULL;
    return newSeperator;
}

void displaySeperator(seperator *seperator)
{
    if (seperator != NULL && seperator->head_p != NULL)
    {
        seperatorNode *tmp = seperator->head_p;
        while (tmp != NULL)
        {
            logger(I, tmp->word);
            tmp = tmp->next;
        }
    }
}

/*this method dequeue element from the queue,returning 0 if there was empty queue and 1 if
the element been dequeued*/
int removeFirstWord(seperator *seperator)
{
    seperatorNode *temp;
    /*checking if queue isn't empty*/
    if (seperator->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = seperator->head_p;
    /*move the head to the next element*/
    seperator->head_p = seperator->head_p->next;

    /*return to the client the node been removed from the queue*/
    free(temp->word);
    free(temp);
    return SUCCESS;
}

/*This method dequeue all the elements from the queue*/
int romoveAllWords(seperator *sep)
{
    if (sep == NULL)
        return FAILURE;

    while (removeFirstWord(sep))
        ;
    return SUCCESS;
}

int destroySeperator(seperator *sep)
{
    if (sep == NULL)
        return FAILURE;
    romoveAllWords(sep);
    free(sep);
    return SUCCESS;
}

/*this method will copy the content to the client's buffer for the data of the first element without removing it*/
int copyFirstWord(seperator *sep, char **str)
{
    if (sep->head_p == NULL)
        return FAILURE;
    else
    {
        strcpy(*str, sep->head_p->word);
        return SUCCESS;
    }
}