#ifndef _SYMBOL_LIST_H
#define _SYMBOL_LIST_H

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
};

int isSymbol(char *str);
int insertSymbol(char *symbol, int address, char *attribute);
void printSymbols();

#endif