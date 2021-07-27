#ifndef _DATA_GUIDANCE_H
#define _DATA_GUIDANCE_H

#define TOTAL_DATA_GUIDANCE 5
#define EMPTY ""
#define ASCIZ ".asciz"
#define DB ".db"
#define DW ".dw"
#define DH ".dh"
#define SIZE_ASCIZ 1
#define SIZE_DB 1
#define SIZE_DH 2
#define SIZE_DW 4

int isValidData(const char *dataType, char *data);
int isDataGuidanceWord(const char *word);
int getSizeOfGuidanceData(const char *word);
int sizeOfGuidanceDataType(const char *word);

#endif
