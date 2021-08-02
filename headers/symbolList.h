#ifndef _SYMBOL_LIST_H
#define _SYMBOL_LIST_H

#define ATTRIBUTE_CODE "code"
#define ATTRIBUTE_DATA "data"
#define ATTRIBUTE_EXTERNAL "external"

typedef struct symbolListNode
{
    int address;
    char *name;
    char *attribute;
    struct symbolListNode *next;

} symbolListNode;

typedef struct symbolsList
{
    symbolListNode *head_p;
} symbolsList;

symbolsList *initSymbolsList();
symbolsList *getSymbolsList();
char *symbolErrorReason(int errorStatus);
int isSymbolExist(symbolsList *symbols, char *symbolName);
int isValidSymbolName(char *str);
int moveAddressDataTypeSymbolsList(symbolsList *symbols, int amount);
int insertSymbol(symbolsList *symbols, char *symbolName, int address, char *attribute);
void printSymbols(symbolsList *symbols);
int destroySymbolsList(symbolsList *symbols);

#endif
