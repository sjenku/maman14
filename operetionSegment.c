#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/operetionSegment.h"
#include "headers/tools.h"
#include "headers/symbolList.h"
#include "headers/stringSeperator.h"
#include "headers/objectCreator.h"

static operetionInfo validOperations[] = {
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

/* Private */
int totalOperations();
int registerToInt(char *str);
int removeFirstOperetion(operetionSeg *seg);
int removeAllOperetionsFrom(operetionSeg *seg);
int totalOperetionsInSeg(operetionSeg *seg);

/* Public */

/* the size for codedString have to be 'CODE_BUFFER_SIZE' + 1 to hold null char */
int operetionRToCode(int opcode, int funct, int rd, int rt, int rs, char **codedString)
{
    /* allocating temperory memory */
    int status;
    char *emptyStr, *opcodeStr, *functStr, *rdStr, *rtStr, *rsStr;

    emptyStr = (char *)malloc(R_CODE_EMPTY_SIZE + 1); /* +1 stends for null char */
    opcodeStr = (char *)malloc(R_CODE_OPCODE_SIZE + 1);
    functStr = (char *)malloc(R_CODE_FUNCT_SIZE + 1);
    rdStr = (char *)malloc(R_CODE_RD_SIZE + 1);
    rtStr = (char *)malloc(R_CODE_RT_SIZE + 1);
    rsStr = (char *)malloc(R_CODE_RS_SIZE + 1);

    /* code to binary each section and check if it was succesefully */
    if (numberToBinary(opcode, R_CODE_OPCODE_SIZE, &opcodeStr) &&
        numberToBinary(funct, R_CODE_FUNCT_SIZE, &functStr) &&
        numberToBinary(rd, R_CODE_RD_SIZE, &rdStr) &&
        numberToBinary(rt, R_CODE_RT_SIZE, &rtStr) &&
        numberToBinary(rs, R_CODE_RS_SIZE, &rsStr) &&
        numberToBinary(0, R_CODE_EMPTY_SIZE, &emptyStr))
    {
        /* create the coded string */
        strcpy(*codedString, opcodeStr);
        strcat(*codedString, rsStr);
        strcat(*codedString, rtStr);
        strcat(*codedString, rdStr);
        strcat(*codedString, functStr);
        strcat(*codedString, emptyStr);
        strcat(*codedString, "\0");

        status = SUCCESS;
    }
    else
    {
        status = FAILURE;
    }
    /* free memory */
    free(opcodeStr);
    free(rsStr);
    free(rtStr);
    free(rdStr);
    free(functStr);
    free(emptyStr);
    return status;
}

/* the size for codedString have to be 'CODE_BUFFER_SIZE' + 1 to hold null char */
int operetionIToCode(int opcode, int rs, int rt, int immed, char **codedString)
{
    /* allocating temperory memory */
    int status;
    char *opcodeStr, *rsStr, *rtStr, *immedStr;

    /* +1 stends for null char */
    opcodeStr = (char *)malloc(I_CODE_OPCODE_SIZE + 1);
    rsStr = (char *)malloc(I_CODE_RS_SIZE + 1);
    rtStr = (char *)malloc(I_CODE_RT_SIZE + 1);
    immedStr = (char *)malloc(I_CODE_IMMED_SIZE + 1);

    /* code to binary each section and check if it was succesefully */
    if (numberToBinary(opcode, I_CODE_OPCODE_SIZE, &opcodeStr) &&
        numberToBinary(rs, I_CODE_RS_SIZE, &rsStr) &&
        numberToBinary(rt, I_CODE_RT_SIZE, &rtStr) &&
        numberToBinary(immed, I_CODE_IMMED_SIZE, &immedStr))
    {
        /* create the coded string */
        strcpy(*codedString, opcodeStr);
        strcat(*codedString, rsStr);
        strcat(*codedString, rtStr);
        strcat(*codedString, immedStr);
        strcat(*codedString, "\0");
        status = SUCCESS;
    }
    else
    {
        status = FAILURE;
    }
    /* free memory */
    free(opcodeStr);
    free(rsStr);
    free(rtStr);
    free(immedStr);
    return status;
}

/* the size for codedString have to be 'CODE_BUFFER_SIZE' + 1 to hold null char */
int operetionJToCode(int opcode, int reg, int address, char **codedString)
{
    /* allocating temperory memory */
    int status;
    char *opcodeStr, *regStr, *addressStr;

    /* +1 stends for null char */
    opcodeStr = (char *)malloc(J_CODE_OPCODE_SIZE + 1);
    regStr = (char *)malloc(J_CODE_REG_SIZE + 1);
    addressStr = (char *)malloc(J_CODE_ADDRESS_SIZE + 1);
    /* code to binary each section and check if it was succesefully */
    if (numberToBinary(opcode, J_CODE_OPCODE_SIZE, &opcodeStr) &&
        numberToBinary(reg, J_CODE_REG_SIZE, &regStr) &&
        numberToBinary(address, J_CODE_ADDRESS_SIZE, &addressStr))
    {
        /* create the coded string */
        strcpy(*codedString, opcodeStr);
        strcat(*codedString, regStr);
        strcat(*codedString, addressStr);
        strcat(*codedString, "\0");
        status = SUCCESS;
    }
    else
    {
        status = FAILURE;
    }
    /* free memory */
    free(opcodeStr);
    free(regStr);
    free(addressStr);
    return status;
}

int isValidOperetionValue(const char *operetionName, char *values)
{
    seperator *sep;
    int i, numberOfValues, success;
    int length;
    /* guard */
    if (operetionName == NULL || values == NULL)
        return FAILURE;

    /* initial values */
    length = totalOperations();
    sep = initSeprator();

    /* when seperate with comma it's check that is no double comma and comma and begining and
    in the end */
    success = appendStringWithComma(sep, values);
    if (!success)
        return FAILURE;

    numberOfValues = numberOfWords(sep);
    for (i = 0; (i < length) && strcmp(validOperations[i].name, operetionName) != 0; i++)
        ;
    /* not found the operetion name in presaved operetion names */
    if (i == length)
        return FAILURE;

    switch (i)
    { /* logic arithmetic R operetions */
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        if (numberOfValues != 3 ||
            !isRegister(getPointerToWord(sep, 1)) ||
            !isRegister(getPointerToWord(sep, 2)) ||
            !isRegister(getPointerToWord(sep, 3)))
            return FAILURE;
        else
            return SUCCESS;
        break;
        /* copy operetions */
    case 5:
    case 6:
    case 7:
        if (numberOfValues != 2 ||
            !isRegister(getPointerToWord(sep, 1)) ||
            !isRegister(getPointerToWord(sep, 2)))
            return FAILURE;
        else
            return SUCCESS;
        break;
        /*logic arithmetic I */
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        if (numberOfValues != 3 ||
            !isRegister(getPointerToWord(sep, 1)) ||
            !isSignNumberOrNumber(getPointerToWord(sep, 2)) ||
            !isRegister(getPointerToWord(sep, 3)))
            return FAILURE;
        else
            return SUCCESS;
        break;
        /* conditional brancing */
    case 13:
    case 14:
    case 15:
    case 16:
        if (numberOfValues != 3 ||
            !isRegister(getPointerToWord(sep, 1)) ||
            !isRegister(getPointerToWord(sep, 2)) ||
            !isNumbersOrLetters(getPointerToWord(sep, 3)))
            return FAILURE;
        else
            return SUCCESS;
        break;
    /* save to memory operetions */
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        if (numberOfValues != 3 ||
            !isRegister(getPointerToWord(sep, 1)) ||
            !isSignNumberOrNumber(getPointerToWord(sep, 2)) ||
            !isRegister(getPointerToWord(sep, 3)))
            return FAILURE;
        else
            return SUCCESS;
        break;
    /* jmp command */
    case 23:
        if (numberOfValues != 1 ||
            (!isRegister(getPointerToWord(sep, 1)) &&
             !isNumbersOrLetters(getPointerToWord(sep, 1))))
            return FAILURE;
        else
            return SUCCESS;
        break;
    /* la command & call command */
    case 24:
    case 25:
        if (numberOfValues != 1 ||
            !isNumbersOrLetters(getPointerToWord(sep, 1)))
            return FAILURE;
        else
            return SUCCESS;
        break;
    /* stop command */
    case 26:
        if (numberOfValues != 0)
            return FAILURE;
        else
            return SUCCESS;
        break;
    }
    return FAILURE;
}

/* this method code the operetion saved in operetion segment to binary.
    after the operetion coded to binary it's saved to objList that holds all 
    binary code that been created*/
int codeOperetionToBinary(objList *objL, operetionSeg *seg, int index)
{
    operetionNode *oprNode;
    operetionInfo *oprInfo;
    symbolsList *symbols;
    symbolListNode *symbolNode;
    int rs, rd, rt, immed, address, reg;
    /* seperetor will hold the values as invidual words */
    seperator *sep;
    /* this will hold coded binary */
    char *codedString;
    /* guards */
    if (seg == NULL || seg->head_p == NULL)
        return FAILURE;
    if (index >= totalOperetionsInSeg(seg))
        return FAILURE;

    /* set inital values */
    rs = rt = rd = immed = 0;
    /* allocate memory for holding the coded string */
    codedString = (char *)malloc(CODE_BUFFER_SIZE + 1);
    /* retrieve the opretion node from all operetions that saved in operetion segment */
    oprNode = getPointToOpertionFromSeg(seg, index);
    /* get the relative information about that operetion */
    oprInfo = getOperetionInfo(oprNode->name);
    /* init new seperetor */
    sep = initSeprator();
    appendStringWithComma(sep, oprNode->value);
    if (oprInfo->type == 'R')
    {
        /* add | sub | and | or | nor */
        if (oprInfo->opcode == 0)
        {
            rs = registerToInt(getPointerToWord(sep, 1));
            rt = registerToInt(getPointerToWord(sep, 2));
            rd = registerToInt(getPointerToWord(sep, 3));
        }
        /* move | mvhi | mvlo */
        else if (oprInfo->opcode == 1)
        {
            rs = registerToInt(getPointerToWord(sep, 1));
            rt = 0;
            rd = registerToInt(getPointerToWord(sep, 2));
        }
        operetionRToCode(oprInfo->opcode, oprInfo->funct, rd, rt, rs, &codedString);
    }
    else if (oprInfo->type == 'I')
    {
        /* addi | subi | andi | ori | nori */
        if (oprInfo->opcode >= 10 && oprInfo->opcode <= 14)
        {
            rs = registerToInt(getPointerToWord(sep, 1));
            rt = registerToInt(getPointerToWord(sep, 3));
            immed = atoi(getPointerToWord(sep, 2));
        }
        /* bne | beq | blt | bgt */
        else if (oprInfo->opcode >= 15 && oprInfo->opcode <= 18)
        {
            /* for this kind of operetion need to retrieve the symbol for immed*/
            /* get pointer to singelton symbol list */
            symbols = getSymbolsList();
            /* find the symbol passed as 3 param */
            symbolNode = getPointerToSymbol(symbols, getPointerToWord(sep, 3));
            printSymbols(symbols);
            /* calculate the relative address */
            immed = symbolNode->address - oprNode->address;
            /* set first param as rs */
            rs = registerToInt(getPointerToWord(sep, 1));
            /* set second param as rt */
            rt = registerToInt(getPointerToWord(sep, 2));
        }
        /* lb | sb | lw | sw | lh | sh */
        else if (oprInfo->opcode >= 19 && oprInfo->opcode <= 24)
        {
            rs = registerToInt(getPointerToWord(sep, 1));
            immed = atoi(getPointerToWord(sep, 2));
            rt = registerToInt(getPointerToWord(sep, 3));
        }
        operetionIToCode(oprInfo->opcode, rs, rt, immed, &codedString);
    }
    else if (oprInfo->type == 'J')
    {
        /* set initial values */
        reg = address = 0;
        /* point to the list of saved symbols */
        symbols = getSymbolsList();
        /* --------------------------jmp------------------------- */
        if (oprInfo->opcode == 30)
        {
            /* set reg */
            reg = isRegister(getPointerToWord(sep, 1)) ? 1 : 0;
            /* set address ,if it's not register get address of the symbol*/
            if (reg == 0)
            {
                /* find the symbol that saved in the symbolList */
                symbolNode = getPointerToSymbol(symbols, getPointerToWord(sep, 1));
                address = symbolNode->address;
            }
            /* else it's register, address param will be the number of register*/
            else
            {
                address = registerToInt(getPointerToWord(sep, 1));
            }
        }
        /* -----------------------  la | call ------------------------------ */
        else if (oprInfo->opcode == 31 || oprInfo->opcode == 32)
        {
            reg = 0;
            symbolNode = getPointerToSymbol(symbols, getPointerToWord(sep, 1));
            address = symbolNode->address;
        }
        /* -------------------------- stop ----------------------------------- */
        else if (oprInfo->opcode == 63)
        {
            reg = 0;
            address = 0;
        }
        /* code to binary */
        operetionJToCode(oprInfo->opcode, reg, address, &codedString);
    }
    destroySeperator(sep);
    insertBinaryToObj(objL, codedString);
    free(codedString);
    return SUCCESS;
}

int registerToInt(char *reg)
{
    return isRegister(reg);
}

operetionNode *getPointToOpertionFromSeg(operetionSeg *seg, int index)
{
    operetionNode *tmpNode;
    int i;
    /* guards */
    if (seg == NULL || seg->head_p == NULL)
        return NULL;
    if (index >= totalOperetionsInSeg(seg))
        return NULL;

    i = 0;
    tmpNode = seg->head_p;
    while (i < index)
    {
        tmpNode = tmpNode->next;
        i++;
    }
    return tmpNode;
}

int totalOperetionsInSeg(operetionSeg *seg)
{
    int counter;
    operetionNode *tmpNode;
    /* guard */
    if (seg == NULL || seg->head_p == NULL)
        return 0;

    counter = 0;
    tmpNode = seg->head_p;
    while (tmpNode != NULL)
    {
        counter++;
        tmpNode = tmpNode->next;
    }
    return counter;
}

operetionInfo *getOperetionInfo(char *name)
{
    int i, totalOpr;
    totalOpr = totalOperations();
    if (name == NULL)
        return NULL;
    else
    {
        /* iterate to find mathcing operetion name */
        for (i = 0; i < totalOpr; i++)
        {
            if (strcmp(name, validOperations[i].name) == 0)
                return &validOperations[i];
        }
        /* not found */
        return NULL;
    }
}

operetionSeg *initOperetionSegment()
{
    operetionSeg *seg;
    seg = (operetionSeg *)malloc(sizeof(operetionSeg));
    seg->IC = 100;
    seg->head_p = NULL;
    return seg;
}

int isValidOperationName(const char *str)
{
    int i;
    int length = totalOperations();
    for (i = 0; i < length; i++)
    {
        if (strcmp(validOperations[i].name, str) == 0)
            return SUCCESS;
    }
    return FAILURE;
}

int totalOperations()
{
    return sizeof(validOperations) / sizeof(operetionInfo);
}

int insertOperetionTo(operetionSeg *seg, char *operetionName, char *value)
{
    /* variables */
    operetionNode *newNode;
    operetionNode *tmpNode;
    int oprNameLength, valLength;

    /* checking if the params valid */
    if (seg == NULL || operetionName == NULL)
        return FAILURE;

    /* creating new OperetionNode for inserting it to list of operetionSegment */
    newNode = (operetionNode *)malloc(sizeof(operetionNode));

    /* handle copy of operetion name with null char */
    oprNameLength = strlen(operetionName);
    newNode->name = (char *)malloc(oprNameLength + 1); /* +1 stends for '\0' */
    strcpy(newNode->name, operetionName);
    *(newNode->name + oprNameLength) = '\0';

    /* handle insertion of value param */
    if (value != NULL)
    {
        valLength = strlen(value);
        newNode->value = (char *)malloc(valLength + 1);
        strcpy(newNode->value, value);
        *(newNode->value + valLength) = '\0';
    }
    else
    /* insert '\0' if value NULL */
    {
        valLength = 1;
        newNode->value = (char *)malloc(valLength);
        *(newNode->value + valLength) = '\0';
    }

    /* set next pointer */
    newNode->next = NULL;

    /* set instruction counter IC */
    newNode->address = seg->IC;
    seg->IC += IC_INCREASER;
    /* insert First Element */
    if (seg->head_p == NULL)
    {
        seg->head_p = newNode;
    }
    else
    {
        tmpNode = seg->head_p;
        /* iterate to the last element */
        while (tmpNode->next != NULL)
        {
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
    }
    return SUCCESS;
}

/* singelton approach */
operetionSeg *getOperetionSegment()
{
    static operetionSeg *seg;
    if (seg == NULL)
        seg = initOperetionSegment();
    return seg;
}

void printOperetionsSeg(operetionSeg *seg)
{
    operetionNode *tmpNode;
    if (seg != NULL && seg->head_p != NULL)
    {
        tmpNode = seg->head_p;
        while (tmpNode != NULL)
        {
            logger(I, "[Name]:%s,[Value]:%s,[Address]:%d", tmpNode->name, tmpNode->value, tmpNode->address);
            tmpNode = tmpNode->next;
        }
    }
}

int removeFirstOperetion(operetionSeg *seg)
{
    operetionNode *temp;
    /*checking if queue isn't empty*/
    if (seg->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = seg->head_p;
    /*move the head to the next element*/
    seg->head_p = seg->head_p->next;

    /*free memory*/
    free(temp->value);
    free(temp->name);
    free(temp);
    return SUCCESS;
}

int removeAllOperetionsFrom(operetionSeg *seg)
{
    if (seg == NULL)
        return FAILURE;

    while (removeFirstOperetion(seg))
        ;
    return SUCCESS;
}

int destroyOperetionSeg(operetionSeg *seg)
{
    if (seg == NULL)
        return FAILURE;
    removeAllOperetionsFrom(seg);
    free(seg);
    return SUCCESS;
}
