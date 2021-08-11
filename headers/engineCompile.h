#ifndef _ENGINE_COMPILE
#define _ENGINE_COMPILE

/*TODO: Need to transfer to seperate file the isComment etc. */
int isComment(char *str);

void engineWorkFlowForLineFirst(char *line, int lineNumber, char *filename);
void engineWorkFlowForLineSecond(char *line, int lineNumber, char *filename);

/*The Heart of the compiler to asmblly files,this function is running all the proccess for compiling the files*/
void runEngine(int argc, char *argv[]);

#endif
