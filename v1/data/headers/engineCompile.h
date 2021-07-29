#ifndef _ENGINE_COMPILE
#define _ENGINE_COMPILE
#define TOTAL_RULES 1

/*TODO:JUST FOR DEBUGGING-NEED TO BE DELETED FROM THE CLIENT*/
void engineWorkFlowForLine(char *line, int lineNumber, char *filename);

/*The Heart of the compiler to asmblly files,this function is running all the proccess for compiling the files*/
void runEngine(int argc, char *argv[]);

#endif
