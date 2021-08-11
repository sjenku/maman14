#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/tools.h"
#include "headers/stringSeperator.h"

/* Private */
int appendWord(seperator *seperator, char *word);

/* Public */
/* this method seperating the string into individual words seperated by comma,
note: if error eccures it will throw FAILURE status and till error accured
the word that been without an error,would be inserted into the seperator */
int appendStringWithComma(seperator *seperator, char *str)
{
    char *ch;
    int i, charCounter, indexLastComma;
    int totalChars, commaFlag;
    totalChars = strlen(str);

    commaFlag = TRUE;
    /* Seperate the words */
    for (ch = str, i = 0, charCounter = 0; i < totalChars + 1; ch++, i++)
    {
        /* indicates it's a comma so it's end of word */
        if (((*ch) == ',' || (*ch) == '\0') && (commaFlag == FALSE))
        {
            commaFlag = TRUE;
            indexLastComma = i;
            /*charCounter != 0 means that previuos chars isn't comma*/
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
        /* it's mean that the char before is a comma and that is not allowed */
        else if ((*ch) == ',' && commaFlag)
        {
            return FAILURE;
        }
        /* it's not a comma */
        else
        {
            charCounter++;
            if (!isspace(*ch))
                commaFlag = FALSE;
        }
    }
    /* check if the last char is 'comma' ,if it is return failure,otherwise return success */
    for (i = totalChars - 1; isspace(str[i]); i--)
        ;
    if (str[i] == ',')
        return FAILURE;
    else
        return SUCCESS;
}

void appendStringWithSpace(seperator *seperator, char *str)
{
    char *ch;
    int i, charCounter;
    int totalChars;
    totalChars = strlen(str);

    /* Seperate the words */
    for (ch = str, i = 0, charCounter = 0; i < totalChars + 1; ch++, i++)
    {
        /* indicates it's a space so it's end of first word */
        if (isspace(*ch) || (*ch) == '\0')
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
    int lengthWord;
    /* Wrong Input */
    if (seperator == NULL || word == NULL)
        return FAILURE;

    /* Create New Node */
    newNode = (seperatorNode *)malloc(sizeof(newNode));
    lengthWord = strlen(word);
    newNode->word = (char *)malloc(lengthWord + 1); /* +1 stends for null char */
    newNode->next = NULL;
    strcpy(newNode->word, word);
    *(newNode->word + lengthWord) = '\0';

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
int lengthFirstWord(seperator *sep)
{
    if (sep == NULL || sep->head_p == NULL)
        return FAILURE;
    else
    {
        return strlen(sep->head_p->word);
    }
}

/* return the word from the list according to the wordNumber index 
@Param- wordNumber is index of the word in the list ,the first word start at index 1*/

char *getPointerToWord(seperator *seperator, int wordNumber)
{
    seperatorNode *tmpNode;
    int i;
    if (seperator == NULL || seperator->head_p == NULL)
        return NULL;
    else
    {
        tmpNode = seperator->head_p;
        /* iterate threw the list if number of word in list less the wordNumber
        return NULL */
        for (i = 1; i < wordNumber && tmpNode != NULL; i++)
        {
            tmpNode = tmpNode->next;
        }
        if (tmpNode != NULL)
        {
            return tmpNode->word;
        }
        else
            return NULL;
    }
}

/*This method dequeue all the elements from the queue*/
int removeAllWords(seperator *sep)
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
    removeAllWords(sep);
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

int numberOfWords(seperator *seperator)
{
    seperatorNode *tmpNode;
    int counter = 0;
    if (seperator == NULL || seperator->head_p == NULL)
        return 0;
    else
    {
        tmpNode = seperator->head_p;
        while (tmpNode != NULL)
        {
            counter++;
            tmpNode = tmpNode->next;
        }
    }
    return counter;
}

int isEmpty(seperator *seperator)
{
    if (seperator == NULL || seperator->head_p == NULL)
        return SUCCESS;
    else
        return FAILURE;
}

/* this method creates a string from all words inside the seperator list
   NOTE:the responsobility for free memory is on the client side */
char *concenateToStringFrom(seperator *seperator, int wordIndex)
{

    char *resultedString;
    char *currentWord;
    int i, length, totalNumberOfWords;

    length = 0;
    totalNumberOfWords = numberOfWords(seperator);
    if (isEmpty(seperator) || totalNumberOfWords < wordIndex)
        return NULL;
    else
    {
        /* figure out how much memory need to be allocated to concenate the words from the list */
        for (i = wordIndex; i <= totalNumberOfWords; i++)
        {
            currentWord = getPointerToWord(seperator, i);
            length += strlen(currentWord);
        }

        /* allocate memory for the end string */
        resultedString = (char *)malloc(length);

        /* copy the first word to the string */
        currentWord = getPointerToWord(seperator, wordIndex);
        strcpy(resultedString, currentWord);

        /* cancentae the rest words */
        for (i = wordIndex + 1; i <= totalNumberOfWords; i++)
        {
            /* set space between the words */
            strcat(resultedString, " ");
            currentWord = getPointerToWord(seperator, i);
            strcat(resultedString, currentWord);
        }
        /* end with null char */
        strcat(resultedString, "\0");
        return resultedString;
    }
}
