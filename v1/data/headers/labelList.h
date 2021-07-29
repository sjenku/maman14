#ifndef _LABELS_LIST
#define _LABELS_LIST

#define SUCCESS 1
#define FAILURE 0
#define ATTRIBUTE_CODE "code"
#define ATTRIBUTE_DATA "data"

typedef struct labelNode
{
    char *name;
    int adrress;
    char *attribute;
    struct labelNode *next;
} labelNode;

typedef struct labelsList
{
    labelNode *head;
} labelsList;

int addLabel(labelsList *labelList, char *name, int adderss, char *labelAttribute);
void printLabelsFrom(labelNode *head);
int isLabelLine(const char *line);
void destoryLabelList(labelsList *labelsList);
int labelExist(labelsList *list, char *name);
labelsList *initLabelsList();

#endif
