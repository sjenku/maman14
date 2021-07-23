#include <stdio.h>
#include <stdarg.h>
#include "../headers/tools.h"

/*Array of total logger types, the indexes of the array relative to the enum 'LoggerType',
for example if client intrested in the logger be on to specific type,it's handled by calling 'loggerOn' method that changes
the index of relative to the enum logger type to 1*/
static int switchers[TOTAL_LOGGER_TYPES];

void loggerOn(int loggerType)
{
    if (loggerType >= 0 && loggerType <= TOTAL_LOGGER_TYPES)
    {
        switchers[loggerType] = 1;
    }
}

void loggerOff(int loggerType)
{
    if (loggerType >= 0 && loggerType <= TOTAL_LOGGER_TYPES)
    {
        switchers[loggerType] = 0;
    }
}

/*
void loggerError(const char *errorInfo, const char *filename, int lineNumber)
{
    printf("[ERROR][FILENAME]:%s[LINE]:%d,%s\n", filename, lineNumber, errorInfo);
}*/

void logger(int loggerType, const char *format, ...)
{
    va_list args;
    if (switchers[loggerType]) /*checking if the switcher for loggertype is ON*/
    {
        va_start(args, format);
        switch (loggerType)
        {
        case 0:
            printf("[Logger]:");
            break;
        case 1:
            printf("[INFO]:");
            break;
        case 2:
            printf("[ERROR]:");
            break;
        case 3:
            printf("[DEBUG]:");
            break;
        }
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
}
