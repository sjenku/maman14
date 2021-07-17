#ifndef _ERRORS_H
#define _ERRORS_H
#define TEMP_BUFFER_SIZE 80

typedef struct error
{
    int status;
    char *info;

} error;

error *newError(int status, const char *info, ...);
void destroyError(error *err);

#endif
