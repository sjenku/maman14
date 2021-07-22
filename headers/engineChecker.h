#ifndef _ENGINE_CHECKER_H
#define _ENGINE_CHECKER_H

#define WORD_LABEL 2000
#define WORD_OPERATION 2001
#define WORD_COMMENT 2002
#define NO_WORD 2003
#define NIETHER 2004

#include "response.h"

int isComment(char *word);
int isOperation(const char *word);
int wordType(const char *word);
int isLabel(char *word);

#endif
