#ifndef _ENGINE_COMPILE
#define _ENGINE_COMPILE

#define TOTAL_RULES 1

typedef struct engineDB
{
    queue *queue;             /*the queue will hold temerory seperated words in each line*/
    symbolsList *symbolsList; /*the list will hold the all symbols fetched from the file*/
} engineDB;

/*The Heart of the compiler to asmblly files,this function is running all the proccess for compiling the files*/
void runEngine(int argc, char *argv[]);

/*this function is initialize the Data Base for the engine*/
engineDB *initEngineDB();

/*TODO:JUST FOR DEBUGGING-NEED TO BE DELETED FROM THE CLIENT*/
void engineWorkFlow(char *line);

#endif
