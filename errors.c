#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "headers/errors.h"
#include "headers/tools.h"

error *newError(int status, const char *info, ...)
{
    error *err;
    va_list args;
    va_start(args, info);
    err = (error *)malloc(sizeof(error));
    /*In case memory allocation not successefull*/
    if (err == NULL)
        return NULL;
    /*set status*/
    err->status = status;

    /*check if info exist,if does then allocate memory for this*/
    if (info != NULL)
    {
        char buffer[TEMP_BUFFER_SIZE];
        err->info = (char *)malloc(vsprintf(buffer, info, args));
        strcpy(err->info, buffer);
        va_end(args);
    }

    return err;
}

void destroyError(error *err)
{
    if (err == NULL)
        return;

    /*if data exist in error,release it*/
    if (err->info != NULL)
        free(err->info);
    /*free from memory*/
    free(err);
}
