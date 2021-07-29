#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>

/* this defines for enqueueStringSeperateWith only,
   be used when this method called replacing the last three param */
#define SEPERATE_WITH_SPACE ' ', ' ', '\t'
#define SEPERATE_WITH_COMMA ',', ',', ','
#define SEPERATE_WITH_SPACEANDCOMMA ' ', ',', '\t'

typedef struct node
{
    char *data;
    struct node *next;
} node;

typedef struct queue
{
    node *headP;
    node *tailP;
} queue;

queue *initQueue();
int enqueue(queue *queue, const char *word);
void enqueueStringSeperateWith(queue *queue, char *str, char seperator1, char seperator2, char seperator3);
int dequeue(queue *q);
int dequeueAll(queue *q);
int destroyQueue(queue *q);
void display(node *headP);
int isEmpty(queue *q);
int peek(queue *q, char **str);
size_t sizeDataFirstElement(queue *q);
int sizeOfQueueData(queue *q);
void catToStringWithSpace(queue *q, char *str);

#endif
