#ifndef _OPERETION_SEGMENT_H
#define _OPERETION_SEGMENT_H

#define IC_INCREASER 4

typedef struct operetionInfo
{
    char *name;
    char type;
    int funct;
    int opcode;
} operetionInfo;

typedef struct operetionNode
{
    char *name;
    char *value;
    int address;
    struct operetionNode *next;

} operetionNode;

typedef struct operetionSegment
{
    operetionNode *head_p;
    int IC;
} operetionSeg;

operetionSeg *getOperetionSegment();
char *toMachineCode(char *operetion);
void printOperetionsSeg(operetionSeg *seg);
operetionSeg *initOperetionSegment();
int isValidOperationName(const char *str);
int isValidOperetionValue(const char *value);
int destroyOperetionSeg(operetionSeg *seg);
int insertOperetionTo(operetionSeg *seg, char *operetion, char *value);

#endif
