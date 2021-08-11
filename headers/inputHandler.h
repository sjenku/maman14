#ifndef _INPUT_HANDLER
#define _INPUT_HANDLER

#define MAX_CHARS_INLINE 80
/*This function takes as argument
@param void (*rulesArr)(char*,int,char*)) - it's function that takes each line from file and implement function on this line.*/
void runRulessOnLinesOfFile(char *filename, void (*rulesFunc)(char *, int, char *));

#endif
