#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/objectCreator.h"
#include "headers/tools.h"

/* manage data of the list */
/* operetionHolding and dataHolding is address holding each segment ICF-INITIAL_ADDRESS & DFC */
int createObjDataToFile(objList *objL, int operetionsHolding, int dataHolding, char *filename)
{
    /* tmpNode for iterate threw the list of object data */
    objNode *tmpNode;
    /* stores the hex representation of binary code that stored in objectlist in each node */
    char *dataHex;
    /* stores the file name with the extension */
    char *fname;
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
        logger(D, "one");
        fname = createFileNameWithExtension(filename, "ob");
        logger(D, "two");
        fileObj = fopen(fname, "w");
        if (fileObj == NULL)
            return FAILURE;
        /* iterate threw list */
        fprintf(fileObj, "\t %d %d ", operetionsHolding, dataHolding);
        while (tmpNode != NULL)
        {
            /* dataHex holding the hexedecimal representation of a binary code 
               'binaryToHex' return allocated str,that need to be free after */
            dataHex = binaryToHex(tmpNode->codedBinary, FROM_RIGHT);
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
        free(fname);
        fclose(fileObj);
        return SUCCESS;
    }
    return FAILURE;
}

/* menage the list */

int insertBinaryToObj(objList *objL, char *binStr)
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
