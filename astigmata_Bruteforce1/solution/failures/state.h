#ifndef INCLUDED_STATE_H
#define INCLUDED_STATE_H 1

typedef struct _STATE
{
    DWORD eax;
    DWORD ebx;
    unsigned char CF;
} STATE, *PSTATE;

#endif
