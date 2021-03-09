#include <windows.h>
#include <stdarg.h>
#include <stdio.h>

void ReportError(char * fmtstr, ...)
{
	CHAR msg_caller[256];
    CHAR msg_gle[256];
    va_list v1;
    va_start(v1,fmtstr);
    vsprintf(msg_caller,fmtstr,v1);
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,0,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),msg_gle,256,0);
    printf("ERROR: %s\nGetLastError() reports: %s",msg_caller,msg_gle);
    va_end(v1);
}
