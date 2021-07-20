#ifndef _RESPONSE_H
#define _RESPONSE_H
#define TEMP_BUFFER_SIZE 80

typedef struct response
{
    int status;
    char *info;

} response;

response *newResponse(int status, const char *info, ...);
void destroyResponse(response *res);

#endif
