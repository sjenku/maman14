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

typedef struct objNode
{
    char *codedBinary;
    /* style will hold or STYLE_DATA or STYLE_OPERETION or STYLE_DIFF ,to indecate in witch feshion parse to hex*/
    int style;
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
int insertBinaryToObj(objList *objL, int style, char *binStr);
void printObjList(objList *objL);
int destroyObjList(objList *objL);
int removeAllObjectsFrom(objList *objL);
int removeFirstObjNode(objList *objL);

/* manager data of the list */
int createObjDataToFile(objList *objL);
int convertHexStyleOpretion(char **hexStr);
int convertHexStyleData(char **hexStr);
int createFileOB();

#endif
