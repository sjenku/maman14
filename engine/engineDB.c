#include <stdio.h>
#include <stdlib.h>
#include "../headers/engineDB.h"

/*This Method Return pointer to new DATABASE*/
engineDB *initEngineDB()
{
    engineDB *db;
    /*Init pointer to the data base*/
    db = (engineDB *)malloc(sizeof(engineDB));
    /*if not enough memory,return NULL*/
    if (db == NULL)
        return NULL;
    /*Init pointer to the queue*/
    db->queue = initQueue();
    /*handle not enough memory when allocating memory*/
    if (db->queue == NULL)
    {
        free(db);
        return NULL;
    }
    /*Init symbols list*/
    db->symbolsList = initSymbolsList();
    /*handle not enough memory during allocation of memory*/
    if (db->symbolsList == NULL)
    {
        free(db);
        return NULL;
    }
    /*init DC- Data Counter*/
    db->DC = 0;
    /*init IC - Instruction Counter*/
    db->IC = 100;
    /*return new Data Base for engine*/
    return db;
}

void destroyEngineDB(engineDB *db)
{
    if (db == NULL)
        return;

    destroyQueue(db->queue);
    destorySymbolList(db->symbolsList);
    free(db);
}

/*return the data base used as a connector between multiple methods used on input line*/
engineDB *getEngineDB()
{
    static engineDB *db;
    if (db == NULL)
        db = initEngineDB();
    return db;
}
