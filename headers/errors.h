#ifndef ERRORS_H
#define ERRORS_H

typedef struct error
{
    int status;
    char *info;
    struct error *next;

} error;

typedef struct errors
{
    error *head_p;
} errors;

errors *initErrorsList();
int insertErrorTo(errors *errors, int status, char *info);
int printErrors(errors *errors);
int destroyFirstError(errors *errors);
int destroyAllErrors(errors *errors);
int destroyErrorsList(errors *errors);

#endif
