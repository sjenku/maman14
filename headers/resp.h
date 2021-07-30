#ifndef _RESP_H
#define _RESP_H

#define STATUS_OK 200
#define STATUS_FAILED 400

typedef struct respNode
{
    int status;
    char *info;
} respNode;

#endif