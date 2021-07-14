#ifndef _INPUT_HANDLER
#define _INPUT_HANDLER

static enum LoggerType { L,
                         I,
                         E
} logT;

typedef struct operetion
{
    char *name;
    char type;
    int funct;
    int opcode;
} operetion;

int isCommentLine(char *line);
void printOperetions();
void readPrintLineFile(int argc, char *argv[]);

#endif