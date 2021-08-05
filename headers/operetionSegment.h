#ifndef _OPERETION_SEGMENT_H
#define _OPERETION_SEGMENT_H

#define IC_INCREASER 4
#define R_CODE_BUFFER_SIZE 32
#define R_CODE_EMPTY_SIZE 6
#define R_CODE_FUNCT_SIZE 5
#define R_CODE_RD_SIZE 5
#define R_CODE_RT_SIZE 5
#define R_CODE_RS_SIZE 5
#define R_CODE_OPCODE_SIZE 6
#define MAX_REGISTER 32

typedef struct operetionR
{
    unsigned int empty : R_CODE_EMPTY_SIZE;
    unsigned int funct : R_CODE_FUNCT_SIZE;
    unsigned int rd : R_CODE_RD_SIZE;
    unsigned int rt : R_CODE_RT_SIZE;
    unsigned int rs : R_CODE_RS_SIZE;
    unsigned int opcode : R_CODE_OPCODE_SIZE;
} operetionR;

typedef struct operetionInfo
{
    char *name;
    char type;
    int funct;
    int opcode;
} operetionInfo;

typedef struct operetionNode
{
    char *name;
    char *value;
    int address;
    struct operetionNode *next;

} operetionNode;

typedef struct operetionSegment
{
    operetionNode *head_p;
    int IC;
} operetionSeg;

/*private*/
int isRegister(char *str);
int isSignNumberOrNumber(char *str);

/*public*/
operetionSeg *getOperetionSegment();
int numberToBinary(int numValue, int sizeOfBits, char **codedString);
int operetionRToCode(operetionR *oprR, char *codedString);
char *fromOperetionToMachineCode(char *operetion, int address);
void printOperetionsSeg(operetionSeg *seg);
int isValidOperetionValue(const char *operetionName, char *values);
int isValidOperetionValueR(char *values);
int isValidOperetionValueJ(char *values);
operetionSeg *initOperetionSegment();
int isValidOperationName(const char *str);
int destroyOperetionSeg(operetionSeg *seg);
int insertOperetionTo(operetionSeg *seg, char *operetion, char *value);

#endif
