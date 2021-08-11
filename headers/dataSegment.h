#ifndef _DATA_SEGMENT_H
#define _DATA_SEGMENT_H

#define TOTAL_DIRECTIVE_WORDS 4
#define ASCIZ ".asciz"
#define DB ".db"
#define DW ".dw"
#define DH ".dh"

#define SIZE_BYTE 8
#define NEGATIVE 0
#define POSITIVE 1
#define MAX_VAL_POSITIVE_BYTE 127
#define MAX_VAL_NEGATIVE_BYTE -128
#define MAX_VAL_POSITIVE_2_BYTE 32767
#define MAX_VAL_NEGATIVE_2_BYTE -32768
#define MAX_VAL_POSITIVE_4_BYTE 2147483647
#define MAX_VAL_NEGATIVE_4_BYTE -2147483648

#include "objectCreator.h"

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
int removeAllDataFrom(dataSeg *seg);
int directiveTypeSize(const char *directiveName);
int directiveAscizToCode(objList *objL, char *value);
int directiveDbDhDwToCode(objList *objL, char *directiveType, char *value);
directiveNode *getPointToDirectiveNode(dataSeg *seg, int index);
int isExternal(char *str);
int isEntry(char *str);
int sizeOfValueBytes(char *dataType, char *value);
void printDataSeg(dataSeg *seg);
dataSeg *initDataSegment();
int moveAddressDataSeg(dataSeg *seg, int amount);
int destroyDataSeg(dataSeg *seg);
int isValidDirectiveName(const char *str);
int isValidDirectiveValues(const char *directiveType, char *str);
int destroyDataSeg(dataSeg *seg);
char *directiveErrorReason(int errorStatus);
int insertDirectiveTo(dataSeg *seg, char *directiveName, char *value);

/* tmp */
int isValidDirectiveValuesDbDhDw(const char *directiveType, char *str);

#endif
