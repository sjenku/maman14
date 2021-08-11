#ifndef ERRORS_H
#define ERRORS_H

typedef struct error
{
    char *info;
    char *filename;
    char *errorTrigger;
    int lineNumber;
    struct error *next;

} error;

typedef struct errors
{
    error *head_p;
} errors;

errors *initErrorsList();
int printErrors(errors *errors);
int insertErrorTo(errors *errors, char *filename, int lineNumber, char *errorTriger, char *info);
int removeFirstError(errors *errors);
int removeAllErrors(errors *errors);
int destroyErrorsList(errors *errors);
int isEmptyErrorList(errors *errors);
/*
char *getErrorInfo(int errorNumber);
*/
errors *getErrorList();
#endif
