#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../headers/response.h"
#include "../headers/tools.h"

response *newResponse(int status, const char *info, ...)
{
    response *res;
    va_list args;
    va_start(args, info);
    res = (response *)malloc(sizeof(response));
    /*In case memory allocation not successefull*/
    if (res == NULL)
        return NULL;
    /*set status*/
    res->status = status;
    /*check if info exist,if does then allocate memory for this*/
    if (info != NULL)
    {
        char buffer[TEMP_BUFFER_SIZE];
        res->info = (char *)malloc(vsprintf(buffer, info, args));
        strcpy(res->info, buffer);
        va_end(args);
    }

    return res;
}

void destroyResponse(response *res)
{
    if (res == NULL)
        return;

    /*if data exist in error,release it*/
    if (res->info != NULL)
        free(res->info);
    /*free from memory*/
    free(res);
}
