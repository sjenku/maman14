#include <string.h>
#include <stdlib.h>
#include "headers/errors.h"
#include "headers/tools.h"

/* Private */
error *newError(int status, char *info);

/* Public Methods Implementation */
error *newError(int status, char *info)
{

    /* variables */
    error *err;
    int strLength;

    /* guard */
    if (info == NULL)
        return NULL;

    /* allocate memory for 'error' */
    strLength = strlen(info);
    err = (error *)malloc(sizeof(error));
    err->info = (char *)malloc(strLength + 1);

    /* insert the info */
    err->status = status;
    err->next = NULL;
    strcpy(err->info, info);

    /* set the last char to be null char */
    *(err->info + strLength) = '\0';

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
        logger(E, tmpNode->info);
        tmpNode = tmpNode->next;
    }
    return SUCCESS;
}

int insertErrorTo(errors *errors, int status, char *info)
{
    error *tmpErr;
    if (errors == NULL || info == NULL)
        return FAILURE;

    /* empty errors list - insert to the head of the list */
    if (errors->head_p == NULL)
    {
        errors->head_p = newError(status, info);
    }
    /* list of errors not empty */
    else
    {
        tmpErr = errors->head_p;
        while (tmpErr->next != NULL)
        {
            tmpErr = tmpErr->next;
        }
        tmpErr->next = newError(status, info);
    }
    return SUCCESS;
}

int destroyFirstError(errors *errors)
{
    error *temp;
    /*checking if errors list isn't empty*/
    if (errors->head_p == NULL)
        return FAILURE;

    /*creating temp pointer to point on the element that would be removed from the queue*/
    temp = errors->head_p;
    /*move the head to the next element*/
    errors->head_p = errors->head_p->next;

    /*return to the client the node been removed from the queue*/
    free(temp->info);
    free(temp);
    return SUCCESS;
}

/*This method delete all the elements from the errors list*/
int destroyAllErrors(errors *errors)
{
    if (errors == NULL)
        return FAILURE;

    while (destroyFirstError(errors))
        ;

    return SUCCESS;
}

/*This method should be used when finish using the errors list,the main reason is to avoid memory leak*/
int destroyErrorsList(errors *errors)
{
    if (errors == NULL)
        return FAILURE;
    destroyAllErrors(errors);
    free(errors);
    return SUCCESS;
}
