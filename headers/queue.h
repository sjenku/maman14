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

queue *initQueue();
int enqueue(queue *queue, char *word);
int dequeue(queue *q);
int dequeueAll(queue *q);
int peek(queue *q, char **str);
void display(node *headP);
void enqueueWordsFromString(queue *queue, char *str);

#endif
