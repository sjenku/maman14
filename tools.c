#include <stdio.h>
#include <stdarg.h>

void logger(int loggerType, const char *format, ...)
{
    va_list args;
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
    }
    vprintf(format, args);
    printf("\n");
    va_end(args);
}
