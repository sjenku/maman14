#ifndef _OBJECT_CREATOR_H
#define _OBJECT_CREATOR_H

#define STYLE_DATA 1
#define SIZE_OBJ_LINE 16
#define STYLE_OPERETION 2
#define STYLE_DIFF 3
#define BUFFER_SIZE 8
#define INITIAL_ADDRESS 100
#define THREE_DIGIT_NUMBER 999
#define ADDRESS_INCREASION 4
#define FROM_RIGHT 1
#define FROM_LEFT 0

typedef struct objNode
{
    char *codedBinary;
    struct objNode *next;
} objNode;

typedef struct objList
{
    objNode *head_p;
    int address;
} objList;

/* standard list operetions */
objList *initObjectList();
objList *getObjectList();
int insertBinaryToObj(objList *objL, char *binStr);
void printObjList(objList *objL);
int destroyObjList(objList *objL);
int removeAllObjectsFrom(objList *objL);
int removeFirstObjNode(objList *objL);

/* manager data of the list */
int createObjDataToFile(objList *objL, int operetionsHolding, int dataHolding, char *filename);

#endif
