#ifndef _TOOLS_H
#define _TOOLS_H

#define SUCCESS 1
#define FAILURE 0

static enum LoggerType { L,
                         I,
                         E
} logT;

void logger(int loggerType, const char *format, ...);

#endif