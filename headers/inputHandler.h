#ifndef _INPUT_HANDLER
#define _INPUT_HANDLER

#define MAX_CHARS_INLINE 80
/*This function takes as argument
@param argc - number of files to compile
@param argv - names of the files
@param numOfRules - number of functions in the array (rulesArr[])
@param void (*rulesArr[])(char*)) - it's array of functions that takes line from file and implement each function in the array on this line.*/
void runRulessOnLinesOfFile(int argc, char *argv[], int numOfRules, void (*rulesArr[])(char *, int, char *));

#endif
