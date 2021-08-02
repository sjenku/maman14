#ifndef _DATA_SEGMENT_H
#define _DATA_SEGMENT_H

#define TOTAL_DIRECTIVE_WORDS 4
#define ASCIZ ".asciz"
#define DB ".db"
#define DW ".dw"
#define DH ".dh"

typedef struct directiveNode
{
    char *name;
    char *value;
    int address;
    struct directiveNode *next;

} directiveNode;

typedef struct dataSegment
{
    directiveNode *head_p;
    int DC;
} dataSeg;

dataSeg *getDataSegment();
int isExternal(char *str);
int sizeOfValue(char *dataType, char *value);
void printDataSeg(dataSeg *seg);
dataSeg *initDataSegment();
int moveAddressDataSeg(dataSeg *seg, int amount);
int destroyDataSeg(dataSeg *seg);
int isValidDirectiveName(const char *str);
int isValidDirectiveValues(const char *directiveType, char *str);
int destroyDataSeg(dataSeg *seg);
int insertDirectiveTo(dataSeg *seg, char *directiveName, char *value);

#endif
