#ifndef _SYMBOLS_LIST
#define _SYMBOLS_LIST

#define SUCCESS 1
#define FAILURE 0

typedef struct symbolNode
{
    char *name;
    int adrress;
    struct symbolNode *next;
} symbolNode;

typedef struct symbolsList
{
    symbolNode *head;
} symbolsList;

int addSymbol(symbolsList *symbolList, char *name, int adderss);
void printSymbolsFrom(symbolNode *head);

#endif