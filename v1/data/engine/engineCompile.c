
#include <stdlib.h>
#include <string.h>
#include "headers/tools.h"
#include "headers/inputHandler.h"
#include "headers/engineCompile.h"

/* this method takes the first word label and second word in the line and insert if no duplicates to the data base */
void handleCaseFirstWordLabel(const char *word, const char *secondWord, char *restLine, const char *filename, int lineNumber)
{
}

/* this function set the workflow that actually the algorithm that handle each line */
void engineWorkFlowForLine(char *line, int lineNumber, char *filename)
{
}

void runEngine(int argc, char *argv[])
{
    void (*rulesArr[TOTAL_RULES])(char *line, int lineNumber, char *filename); /*Array of functions(Rules) applied to handle each line*/

    rulesArr[0] = engineWorkFlowForLine;
    runRulessOnLinesOfFile(argc, argv, TOTAL_RULES, rulesArr);
}
