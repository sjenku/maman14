#ifndef _ASMB_OPERATION
#define _ASMB_OPERATION

typedef struct operetion
{
    char *name;
    char type;
    int funct;
    int opcode;
} operetion;

void printOperetions();
int isOperationValid(const char *operationName);

#endif
