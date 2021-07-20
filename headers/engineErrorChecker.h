#ifndef _ENGINE_ERROR_CHECKER_H
#define _ENGINE_ERROR_CHECKER_H

#include "response.h"

int isComment(char *word);
int isOperation(const char *word);
response *isSymbol(char *word);

#endif
