#ifndef _ENGINE_COMPILE
#define _ENGINE_COMPILE
#define TOTAL_RULES 1

/*TODO: Need to transfer to seperate file the isComment etc. */
int isComment(char *str);

void engineWorkFlowForLine(char *line, int lineNumber, char *filename);

/*The Heart of the compiler to asmblly files,this function is running all the proccess for compiling the files*/
void runEngine(int argc, char *argv[]);

#endif
