#include <string.h>
#include <stdlib.h>
#include "headers/errors.h"
#include "headers/tools.h"

/* Private */
error *newError(char *filename, int lineNumber, char *errorTrigger, char *info);

/* Public Methods Implementation */
error *newError(char *filename, int lineNumber, char *errorTrigger, char *info)
{

    /* variables */
    error *err;
    int strLength;

    /* allocate memory for 'error' */
    strLength = strlen(info);
    err = (error *)malloc(sizeof(error));
    /* allocate memory for info */
    err->info = (char *)malloc(strLength + 1);
    /* insert the info */
    strcpy(err->info, info);
    /* set the last char to be null char */
    *(err->info + strLength) = '\0';

    /* allocate memory for filename */
    strLength = strlen(filename);
    err->filename = (char *)malloc(strLength + 1);
    /* insert the filename */
    strcpy(err->filename, filename);
    *(err->filename + strLength) = '\0';

    /* this the only value that allowed to be NULL */
    if (errorTrigger != NULL)
    {
        /*allocate memory for errorTriger */
        strLength = strlen(errorTrigger);
        err->errorTrigger = (char *)malloc(strLength + 1);
        /* insert the error trigger */
        strcpy(err->errorTrigger, errorTrigger);
        *(err->errorTrigger + strLength) = '\0';
    }
    else
    {
        err->errorTrigger = NULL;
    }
    /* set next */
    err->next = NULL;
    err->lineNumber = lineNumber;

    return err;
}

errors *initErrorsList()
{
    errors *errs;
    errs = (errors *)malloc(sizeof(errors));
    errs->head_p = NULL;
    return errs;
}

int printErrors(errors *errors)
{
    error *tmpNode;
    if (errors == NULL)
        return FAILURE;

    tmpNode = errors->head_p;
    while (tmpNode != NULL)
    {
        logger(E, "[Filename]:%s,[Line]:%d,[ErrorReason]:%s,[Info]:%s", tmpNode->filename, tmpNode->lineNumber, tmpNode->errorTrigger, tmpNode->info);
        tmpNode = tmpNode->next;
    }
    return SUCCESS;
}

int isEmptyErrorList(errors *errors)
{
    if (errors == NULL || errors->head_p == NULL)
        return SUCCESS;
    else
        return FAILURE;
}

int insertErrorTo(errors *errors, char *filename, int lineNumber, char *errorTrigger, char *info)
{
    error *tmpErr;
    if (errors == NULL || info == NULL || filename == NULL)
        return FAILURE;

    /* empty errors list - insert to the head of the list */
    if (errors->head_p == NULL)
    {
        errors->head_p = newError(filename, lineNumber, errorTrigger, info);
    }
    /* list of errors not empty */
    else
    {
        tmpErr = errors->head_p;
        while (tmpErr->next != NULL)
        {
            tmpErr = tmpErr->next;
        }
        tmpErr->next = newError(filename, lineNumber, errorTrigger, info);
    }
    return SUCCESS;
}

int removeFirstError(errors *errors)
{
    error *temp;
    /*checking if errors list isn't empty*/
    if (errors->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = errors->head_p;
    /*move the head to the next element*/
    errors->head_p = errors->head_p->next;

    /* free memory */
    free(temp->info);
    free(temp->filename);
    if (temp->errorTrigger != NULL) /* error triger can be null */
        free(temp->errorTrigger);
    free(temp);
    return SUCCESS;
}

/*This method delete all the elements from the errors list*/
int removeAllErrors(errors *errors)
{
    if (errors == NULL)
        return FAILURE;

    while (removeFirstError(errors))
        ;

    return SUCCESS;
}

/*This method should be used when finish using the errors list,the main reason is to avoid memory leak*/
int destroyErrorsList(errors *errors)
{
    if (errors == NULL)
        return FAILURE;
    removeAllErrors(errors);
    free(errors);
    return SUCCESS;
}

errors *getErrorList()
{
    static errors *errList;
    if (errList == NULL)
    {
        errList = initErrorsList();
    }
    return errList;
}
/*
char *getErrorInfo(int errorNumber)
{
    switch (errorNumber)
    {
    case ERR_SYMBOL_1:
        return "can't duplicate symbols";
    case ERR_SYMBOL_2:
        return "not valid symbol";
    default:
        return "";
    }
}
*/
