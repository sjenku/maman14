#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/objectCreator.h"
#include "headers/tools.h"

/* private */
void swap(char *ch1, char *ch2);

/* manage data of the list */
int createObjDataToFile(objList *objL)
{
    printObjList(objL);
    /* tmpNode for iterate threw the list of object data */
    objNode *tmpNode;
    /* stores the hex representation of binary code that stored in objectlist in each node */
    char *dataHex;
    /* start address */
    int address;
    /* i - for iterating , length - would hold the length of hex code for each node,
    totalChars - holding the total chars inserted to file from dataHex */
    int i, length, totalChars;
    /* pointer to the file */
    FILE *fileObj;
    if (objL != NULL && objL->head_p != NULL)
    {
        /* inital values */
        address = objL->address;
        tmpNode = objL->head_p;
        i = length = totalChars = 0;
        dataHex = NULL;
        fileObj = fopen("obj.txt", "w");
        logger(D, "creating file");
        if (fileObj == NULL)
            return FAILURE;
        /* iterate threw list */
        while (tmpNode != NULL)
        {
            /* dataHex holding the hexedecimal representation of a binary code 
               'binaryToHex' return allocated str,that need to be free after */
            dataHex = binaryToHex(tmpNode->codedBinary);
            logger(D, "binaryToHex=> %s", dataHex);
            if (tmpNode->style == STYLE_OPERETION)
                convertHexStyleOpretion(&dataHex);
            else if (tmpNode->style == STYLE_DATA)
                convertHexStyleData(&dataHex);
            length = strlen(dataHex);

            /* create format as |adress hex hex hex hex| */
            for (i = 0; i < length; i++, totalChars++)
            {
                /* new line */
                if (totalChars % 8 == 0)
                {
                    putc('\n', fileObj);
                    /* insert address */
                    if (address <= THREE_DIGIT_NUMBER)
                    {
                        fprintf(fileObj, "0%d ", address);
                    }
                    else
                    {
                        fprintf(fileObj, "%d ", address);
                    }
                    address += ADDRESS_INCREASION;
                }
                /* if it's pair of hexs add space between */
                else if (totalChars % 2 == 0)
                {
                    putc(' ', fileObj);
                }
                putc(dataHex[i], fileObj);
            }

            tmpNode = tmpNode->next;
            /* free memory */
            free(dataHex);
        }
        fclose(fileObj);
        return SUCCESS;
    }
    return FAILURE;
}

int convertHexStyleData(char **hexStr)
{
    int i, j;
    i = 0;
    j = strlen(*(hexStr)) - 2;
    while (i < j)
    {
        swap(&(*hexStr)[i], &(*hexStr)[j]);
        swap(&(*hexStr)[i + 1], &(*hexStr)[j + 1]);
        i += 2;
        j -= 2;
    }
}
int convertHexStyleOpretion(char **hexStr)
{
    int i, length;

    i = 0;
    length = strlen(*hexStr);
    if (length < BUFFER_SIZE)
    {
        *hexStr = (char *)realloc(*hexStr, BUFFER_SIZE + 1);
        if (*hexStr == NULL)
            logger(D, "couldn't realloc");
    }
    /* add 'missing' hexs to get hexs in size of buffer_size e.g buffersize 8 then 1FFFF -> 1FFFF000 */
    for (i = length; i < BUFFER_SIZE; i++)
    {
        (*hexStr[i]) = '0';
    }
    /* null char */
    (*hexStr)[BUFFER_SIZE] = '\0';
    swap(&(*hexStr)[0], &(*hexStr)[6]);
    swap(&(*hexStr)[1], &(*hexStr)[7]);
    swap(&(*hexStr)[2], &(*hexStr)[4]);
    swap(&(*hexStr)[3], &(*hexStr)[5]);
    return SUCCESS;
}

void swap(char *ch1, char *ch2)
{
    char tmpCh;
    tmpCh = *ch1;
    *ch1 = *ch2;
    *ch2 = tmpCh;
}

/* menage the list */

/* the style param is STYLE_DATA or STYLE_OPERETION this specify the binary type
    it's neccasery for when objectList creates file with hex representation */
int insertBinaryToObj(objList *objL, int style, char *binStr)
{
    /* variables */
    objNode *newNode, *tmpNode;
    int binStrLength;

    /* checking if the params valid */
    if (objL == NULL || binStr == NULL)
        return FAILURE;

    /* creating new newNode for inserting it to list of objectList */
    newNode = (objNode *)malloc(sizeof(objNode));

    /* handle copy of direvtive name with null char */
    binStrLength = strlen(binStr);
    newNode->codedBinary = (char *)malloc(binStrLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->codedBinary, binStr);
    *(newNode->codedBinary + binStrLength) = '\0';

    /* set next pointer */
    newNode->next = NULL;
    /* set style */
    newNode->style = style;

    /* insert First Element */
    if (objL->head_p == NULL)
    {
        objL->head_p = newNode;
    }
    else
    {
        tmpNode = objL->head_p;
        /* iterate to the last element */
        while (tmpNode->next != NULL)
        {
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
    }
    return SUCCESS;
}

void printObjList(objList *objL)
{
    objNode *tmpNode;
    if (objL != NULL && objL->head_p != NULL)
    {
        tmpNode = objL->head_p;
        while (tmpNode != NULL)
        {
            logger(I, "[Value]:%s", tmpNode->codedBinary);
            tmpNode = tmpNode->next;
        }
    }
}

int destroyObjList(objList *objL)
{
    if (objL == NULL)
        return FAILURE;
    removeAllObjectsFrom(objL);
    free(objL);
    return SUCCESS;
}

int removeAllObjectsFrom(objList *objL)
{
    if (objL == NULL)
        return FAILURE;

    while (removeFirstObjNode(objL))
        ;
    return SUCCESS;
}

int removeFirstObjNode(objList *objL)
{
    objNode *temp;
    /*checking if queue isn't empty*/
    if (objL->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = objL->head_p;
    /*move the head to the next element*/
    objL->head_p = objL->head_p->next;

    /*free memory*/
    free(temp->codedBinary);
    free(temp);
    return SUCCESS;
}

objList *initObjectList()
{
    objList *objL;
    objL = (objList *)malloc(sizeof(objList));
    objL->head_p = NULL;
    objL->address = INITIAL_ADDRESS;
    return objL;
}

objList *getObjectList()
{
    static objList *objL;
    if (objL == NULL)
        objL = initObjectList();
    return objL;
}
