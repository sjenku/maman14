#ifndef _RESPONSE_H
#define _RESPONSE_H
#define TEMP_BUFFER_SIZE 80

typedef struct response
{
    char *info;

} response;

response *newResponse(const char *info, ...);
void destroyResponse(response *res);

#endif
