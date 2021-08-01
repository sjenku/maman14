#ifndef _STRING_SEPERATOR_H
#define _STRING_SEPERATOR_H

typedef struct seperatorNode
{
    char *word;
    struct seperatorNode *next;
} seperatorNode;

typedef struct seperator
{
    seperatorNode *head_p;
} seperator;

void appendString(seperator *seperator, char *str);
seperator *initSeprator();
char *getPointerToWord(seperator *seperator, int wordNumber);
int numberOfWords(seperator *seperator);
char *concenateToStringFrom(seperator *seperator, int wordIndex);
int removeAllWords(seperator *sep);
int lengthFirstWord(seperator *sep);
void displaySeperator(seperator *seperator);
int removeFirstWord(seperator *seperator);
int copyFirstWord(seperator *seperator, char **str);
int removeFirstWord(seperator *seperator);
int destroySeperator(seperator *seperator);
/* private
int appendWord(seperator *seperator, char *word);
*/

#endif
