#include <string.h>
#include "../headers/tools.h"
#include "../headers/dataGuidance.h"

static char *dataGuidance[TOTAL_DATA_GUIDANCE] = {
    ".asciz", ".db", ".dw", ".dh"};

int isDataGuidanceWord(const char *word)
{
    int i;
    int length = TOTAL_DATA_GUIDANCE;
    for (i = 0; i < length; i++)
    {
        if (strcmp(dataGuidance[i], word) == 0)
            return SUCCESS;
    }
    return FAILURE;
}
