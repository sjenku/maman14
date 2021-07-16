#include <string.h>
#include "headers/asmbOperation.h"
#include "headers/tools.h"

static operetion operations[] = {
    {"add", 'R', 1, 0},
    {"sub", 'R', 2, 0},
    {"and", 'R', 3, 0},
    {"or", 'R', 4, 0},
    {"nor", 'R', 5, 0},
    {"move", 'R', 1, 1},
    {"mvhi", 'R', 2, 1},
    {"mvlo", 'R', 3, 1},
    {"addi", 'I', -1, 10},
    {"subi", 'I', -1, 11},
    {"andi", 'I', -1, 12},
    {"ori", 'I', -1, 13},
    {"nori", 'I', -1, 14},
    {"bne", 'I', -1, 15},
    {"beq", 'I', -1, 16},
    {"blt", 'I', -1, 17},
    {"bgt", 'I', -1, 18},
    {"lb", 'I', -1, 19},
    {"sb", 'I', -1, 20},
    {"lw", 'I', -1, 21},
    {"sw", 'I', -1, 22},
    {"lh", 'I', -1, 23},
    {"sh", 'I', -1, 24},
    {"jmp", 'J', -1, 30},
    {"la", 'J', -1, 31},
    {"call", 'J', -1, 32},
    {"stop", 'J', -1, 63}};

int totalOperations()
{
    return sizeof(operations) / sizeof(operetion);
}

void printOperetions()
{
    operetion *oprP;
    int length = totalOperations();
    logger(L, "Length Operetions => %d", length);
    for (int i = 0; i < length; i++)
    {
        oprP = &(operations[i]);
        logger(I, "Name:%s", oprP->name);
    }
}

/*Compare if operationName is equal to one of the presaved operations*/
int isOperationExist(const char *operationName)
{
    int length = totalOperations();
    for (int i = 0; i < length; i++)
    {
        if (strcmp(operations[i].name, operationName) == 0)
            return SUCCESS;
    }
    return FAILURE;
}
