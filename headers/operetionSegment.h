#ifndef _OPERETION_SEGMENT_H
#define _OPERETION_SEGMENT_H

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
    struct operetionNode *next;

} operetionNode;

typedef struct operetionSegment
{
    operetionNode *head_p;
    int IC;
} operetionSeg;

void printOperetionsSeg(operetionSeg *seg);
operetionSeg *initOperetionSegment();
int isValidOperation(const char *str);
int insertOperetionTo(operetionSeg *seg, char *operetion, char *value);

#endif
