#include <stdlib.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/symbolList.h"

#define ERR_1 1001
#define ERR_2 1002

/* Private Methods */

int removeFirstSymbol(symbolsList *symbols);
int removeAllSymbolsFrom(symbolsList *symbols);

/* Public Methods */
char *symbolErrorReason(int errorStatus)
{
    if (errorStatus == ERR_1)
        return "can't appear ':' in the middle of the symbol's name";
    else if (errorStatus == ERR_2)
        return "the symbol have to finish with ':'";
    else
        return "undefined";
}

int isSymbolExist(symbolsList *symbols, char *symbolName)
{
    symbolListNode *tmpNode;
    char *tmpSymbolName;
    int length;
    /* check valid input */
    if (symbols == NULL || symbols->head_p == NULL || symbolName == NULL)
        return FAILURE;
    else
    {
        tmpNode = symbols->head_p;
        /* iterate threw the symbols list and compare with the param symbol */
        while (tmpNode != NULL)
        {
            /* create symbol name with ':' from the saved symbols */
            length = strlen(tmpNode->name) + 2; /* +2 stends for adding ':' and '\0' */
            tmpSymbolName = (char *)malloc(length);
            strcpy(tmpSymbolName, tmpNode->name);
            *(tmpSymbolName + length - 2) = ':';
            *(tmpSymbolName + length - 1) = '\0';
            /* compare symbol from list (tmpSymbolName) with the param symbolName */
            if ((strcmp(tmpSymbolName, symbolName)) == 0)
            {
                free(tmpSymbolName);
                return SUCCESS;
            }
            tmpNode = tmpNode->next;
            free(tmpSymbolName);
        }
        /* didn't found match till the end of the list */
        return FAILURE;
    }
}

int isValidSymbolName(char *str)
{
    int length;
    char *ch;
    int i;
    /* not valid input */
    if (str == NULL)
        return FAILURE;

    length = strlen(str);
    /* check if ends with ':' and there is no ':' in the middle of the string */
    for (ch = str, i = 0; (*ch) != '\0'; ch++, i++)
    {
        /* case the ':' is not the last char */
        if ((*ch) == ':' && i != length - 1)
            return ERR_1;
        else if ((*ch) == ':' && i == length - 1)
            return SUCCESS;
    }

    /* the symbol dosen't finished with ':' */
    return ERR_2;
}

/* use singelton approach */
symbolsList *getSymbolsList()
{
    static symbolsList *symbols;
    if (symbols == NULL)
        symbols = initSymbolsList();
    return symbols;
}

symbolsList *initSymbolsList()
{
    symbolsList *symbols;
    symbols = (symbolsList *)malloc(sizeof(symbolsList));
    symbols->head_p = NULL;
    return symbols;
}

int insertSymbol(symbolsList *symbols, char *symbolName, int address, char *attribute)
{
    int length;
    symbolListNode *newNode;
    symbolListNode *tmpNode;
    if (symbols == NULL)
        return FAILURE;

    length = strlen(symbolName);
    /* create new symbol element( node )*/
    newNode = (symbolListNode *)malloc(sizeof(symbolListNode));
    /* set symbol's name without ':' instead of it replace it with '\0' */
    newNode->name = (char *)malloc(length);
    strcpy(newNode->name, symbolName);
    if (*(newNode->name + length - 1) == ':')
        *(newNode->name + length - 1) = '\0';

    /* set attribute */
    length = strlen(attribute);
    newNode->attribute = (char *)malloc(length + 1); /* +1 stends for null char */
    strcpy(newNode->attribute, attribute);
    *(newNode->attribute + length) = '\0';

    /* set address */
    newNode->address = address;
    /* set next */
    newNode->next = NULL;

    /* Insert first element to the list */
    if (symbols->head_p == NULL)
    {
        symbols->head_p = newNode;
    }
    /* Insert to the end of list */
    else
    {
        tmpNode = symbols->head_p;
        /* iterate to the last element */
        while (tmpNode->next != NULL)
            tmpNode = tmpNode->next;
        /* append */
        tmpNode->next = newNode;
    }
    return SUCCESS;
}

void printSymbols(symbolsList *symbols)
{
    symbolListNode *tmpNode;
    if (symbols != NULL && symbols->head_p != NULL)
    {
        tmpNode = symbols->head_p;
        while (tmpNode != NULL)
        {
            logger(I, "[SYMBOL]:%s,[ADDRESS]:%d,[ATTRIBUTE]:%s", tmpNode->name, tmpNode->address, tmpNode->attribute);
            tmpNode = tmpNode->next;
        }
    }
}

int removeFirstSymbol(symbolsList *symbols)
{
    symbolListNode *tmpNode;
    /*checking if queue isn't empty*/
    if (symbols->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    tmpNode = symbols->head_p;
    /*move the head to the next element*/
    symbols->head_p = symbols->head_p->next;

    /*free memory*/
    free(tmpNode->name);
    free(tmpNode->attribute);
    free(tmpNode);
    return SUCCESS;
}

int removeAllSymbolsFrom(symbolsList *symbols)
{
    if (symbols == NULL)
        return FAILURE;

    while (removeFirstSymbol(symbols))
        ;
    return SUCCESS;
}

int destroySymbolsList(symbolsList *symbols)
{
    if (symbols == NULL)
        return FAILURE;
    removeAllSymbolsFrom(symbols);
    free(symbols);
    return SUCCESS;
}

int moveAddressDataTypeSymbolsList(symbolsList *symbols, int ICF)
{
    symbolListNode *tmpNode;
    if (symbols == NULL || symbols->head_p == NULL)
        return FAILURE;
    else
    {
        tmpNode = symbols->head_p;
        while (tmpNode != NULL)
        {
            /* move the address value only for symbols with data attribute */
            if (strcmp(tmpNode->attribute, ATTRIBUTE_DATA) == 0)
                tmpNode->address += ICF;
            tmpNode = tmpNode->next;
        }
        return SUCCESS;
    }
}

symbolListNode *findSymbol(symbolsList *symbols, char *symbolName)
{
    symbolListNode *tmpNode;
    /* guard */
    if (symbols == NULL || symbols->head_p == NULL)
        return NULL;

    tmpNode = symbols->head_p;
    /* iterate threw the list of symbols */
    while (tmpNode != NULL)
    {
        /* compare the name of symbol with the param symbolName */
        if (strcmp(tmpNode->name, symbolName) == 0)
            return tmpNode;
        tmpNode = tmpNode->next;
    }
    /* not found */
    return NULL;
}

/* this method return FAILURE if symbol not exist and SUCCESS if the attribute changed*/
int changeAttribute(symbolsList *symbolList, char *symbolName, char *attribute)
{
    symbolListNode *symbol;
    int length;
    symbol = findSymbol(symbolList, symbolName);

    /* guard */
    if (symbol == NULL)
        return FAILURE;

    /* free memory of prev attribute */
    free(symbol->attribute);

    /* allocate memory for the new attribute val */
    length = strlen(attribute);
    symbol->attribute = (char *)malloc(length + 1); /* +1 stends for null char */

    /* copy to the new attribute */
    strcpy(symbol->attribute, attribute);
    /* set the null char */
    symbol->attribute[length] = '\0';

    return SUCCESS;
}