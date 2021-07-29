#ifndef _ENGINE_CHECKER_H
#define _ENGINE_CHECKER_H

#define TYPE_LABEL 2000
#define TYPE_OPERATION 2001
#define TYPE_COMMENT 2002
#define TYPE_DATA_GUIDANCE 2003
#define UNDEFINED 2004

#include "response.h"

int isComment(char *word);
int isOperation(const char *word);
int wordType(char *word, const char *filename, int lineNumber);
int isLabel(char *word, const char *filename, int lineNumber);

#endif
