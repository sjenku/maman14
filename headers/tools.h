#ifndef _TOOLS_H
#define _TOOLS_H

#define SUCCESS 1
#define FAILURE 0
#define TOTAL_LOGGER_TYPES 4

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

#endif
