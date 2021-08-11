#ifndef _TOOLS_H
#define _TOOLS_H

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define TOTAL_LOGGER_TYPES 4
#define MAX_REGISTER 32

static enum LoggerType { L,
                         I,
                         E,
                         D
} logT;

void logger(int loggerType, const char *format, ...);
/*
void loggerError(const char *errorInfo, const char *filename, int lineNumber);
*/
void loggerOn(int loggerType);
void loggerOff(int loggerType);

int isSignNumberOrNumber(char *str);
int isNumbersOrLetters(char *str);
int isRegister(char *str);
int numberToBinary(int numValue, int sizeOfBits, char **codedString);
char *binaryToHex(char *inStr, int fromRight);
char *createFileNameWithExtension(char *filename, char *extension);
#endif
