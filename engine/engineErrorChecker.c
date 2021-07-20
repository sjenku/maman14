#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/response.h"
#include "../headers/asmbOperation.h"
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

/*if it's a symbol it will return response type with status 'SUCCESS' or 'FAILURE' and relative info*/
response *isSymbol(char *word)
{
    char *ch;     /*for handle each char in the word*/
    int position; /*position of the current char*/
    char *tmpStr; /*hold temerory substring from begining of the word till ':'*/
    response *res;
    if (word == NULL)
        return NULL;
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
                res = newResponse(FAILURE, "Can't be used '%s' as a symbol,this is an operation name", tmpStr);
                free(tmpStr);
                return res;
            }
            ch = (word + position + 1);        /*check the next letter after ':'*/
            if ((*ch != '\0') && (*ch != ' ')) /*label should end with ';'*/
            {
                res = newResponse(FAILURE, "label should end with ':',label can't finish with a letter '%c'", *ch);
                free(tmpStr);
                return res;
            }
            /*will return the response as found symbol and return the symbols name in the response*/
            res = newResponse(SUCCESS, tmpStr);
            free(tmpStr);
            return res;
        }
    }
    return NULL; /*means that it's not a label and isn't an error*/
}
