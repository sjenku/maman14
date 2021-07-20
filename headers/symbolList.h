#ifndef _SYMBOLS_LIST
#define _SYMBOLS_LIST

#define SUCCESS 1
#define FAILURE 0
#define ATTRIBUTE_CODE "code"
#define ATTRIBUTE_DATA "data"

typedef struct symbolNode
{
    char *name;
    int adrress;
    char *attribute;
    struct symbolNode *next;
} symbolNode;

typedef struct symbolsList
{
    symbolNode *head;
} symbolsList;

int addSymbol(symbolsList *symbolList, char *name, int adderss, char *symbolAttribute);
void printSymbolsFrom(symbolNode *head);
int isSymbolLine(const char *line);
void destorySymbolList(symbolsList *symbolsList);
int symbolExist(symbolsList *list, char *name);
symbolsList *initSymbolsList();

#endif
