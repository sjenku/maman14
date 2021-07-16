#ifndef _QUEUE_H_
#define _QUEUE_H_

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

int enqueue(queue *queue, char *word);
void display(node *headP);
void enqueueWordsFromString(queue *queue, char *str);

#endif