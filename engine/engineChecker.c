#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/response.h"
#include "../headers/asmbOperation.h"
#include "../headers/engineDB.h"
#include "../headers/tools.h"

int isComment(char *word)
{
    /*Temperory char holder of each char in the line*/
    char *ch;
    /*Iterate threw the line*/
    for (ch = word; *ch != '\0'; ch++)
    {
        if (!isspace(*ch))
            /*Checking if the ';' char in the begining
         of the line that indecates that is a comment*/
            if (*ch == ';')
            {
                logger(I, "Is a comment word => %s", word);
                return SUCCESS;
            }
    }
    return FAILURE;
}

int isOperation(const char *word)
{
    return isOperationValid(word);
}

int wordType(const char *word)
{

    //TODO: define the word type and then handle each word type accordingly in the engineWorkFlow
    return 1;
}

/*if it's a label it will return response type with status 'SUCCESS' or 'FAILURE' and relative info*/
int isLabel(char *word)
{
    char *ch;           /* for handle each char in the word */
    int position;       /* position of the current char */
    char *tmpStr;       /* hold temerory substring from begining of the word till ':' */
    response *res;      /* if err accures , generate response that will be added to errors queue in data base */
    engineDB *engineDB; /* central data base of engine */

    /* get pointer to engine data base */
    engineDB = getEngineDB();

    if (word == NULL)
        return FAILURE;
    /*Iterate threw the word*/
    for (ch = word, position = 0; (*ch) != '\0'; ch++, position++)
    {
        /*checking if the letter is ':' if it does then make substring till that char*/
        if ((*ch) == ':')
        {
            /*creating the substring till ':'*/
            tmpStr = (char *)malloc(position);
            strncpy(tmpStr, word, position);
            /*checking if the word till the ':' char isn't a reserved word for assembly operetions */
            if (isOperation(tmpStr))
            {
                /* generate the error to be inserted to the queue of errors */
                res = newResponse("Can't be used '%s' as a label,this is an operation name", tmpStr);
                /* insert to data base the error */
                enqueue(engineDB->errorsQueue, res->info);
                /* free memory */
                free(tmpStr);
                destroyResponse(res);

                return FAILURE;
            }
            /* check the next letter after ':' */
            ch = (word + position + 1);
            /* label should end with ':' */
            if ((*ch != '\0') && (*ch != ' '))
            {
                /* generate the error to be inserted to the queue of errors */
                res = newResponse("label should end with ':',label can't finish with a letter '%c'", *ch);
                /* insert to data base the error */
                enqueue(engineDB->errorsQueue, res->info);
                /* free memory */
                free(tmpStr);
                destroyResponse(res);

                return FAILURE;
            }
            /* it's a label */
            free(tmpStr);
            return SUCCESS;
        }
    }
    return FAILURE; /*means that it's not a label and isn't an error*/
}
