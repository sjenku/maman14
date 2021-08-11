#ifndef _EXT_CREATOR_H
#define _EXT_CREATOR_H

#define MAX_NAMEFILE_CHARS 80

typedef struct extNode
{
    int address;
    char *name;
    struct extNode *next;
} extNode;

typedef struct extList
{
    extNode *head_p;
} extList;

int insertExtTo(extList *extL, char *name, int address);
extList *initExtList();
extList *getExtList();
int createExtFileFrom(extList *extL, char *filename);

#endif
