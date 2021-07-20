#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>

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
int enqueue(queue *queue, char *word);
void enqueueWordsFromString(queue *queue, char *str);
int dequeue(queue *q);
int dequeueAll(queue *q);
int destroyQueue(queue *q);
void display(node *headP);
int peek(queue *q, char **str);
size_t sizeDataFirstElement(queue *q);

#endif
