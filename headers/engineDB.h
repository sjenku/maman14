#ifndef _ENGINE_DB_H
#define _ENGINE_DB_H

#include "queue.h"
#include "labelList.h"

typedef struct engineDB
{
    queue *errorsQueue;     /*the queue will hold temerory seperated words in each line*/
    labelsList *labelsList; /*the list will hold the all labels fetched from the file*/
    int DC;
    int IC;
} engineDB;

engineDB *initEngineDB();

/*this function is initialize the Data Base for the engine*/
engineDB *initEngineDB();
/*this function return the data base*/
engineDB *getEngineDB();

/*remove all elements of the engine data base and free memory*/
void destroyEngineDB(engineDB *db);

#endif
