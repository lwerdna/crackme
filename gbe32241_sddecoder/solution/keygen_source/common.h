/*************************************************************
 *
 * MISC. FUNCTIONS
 *
 *************************************************************/

#define ERRCLEANUP(FMT,...) { ReportError((FMT,__VA_ARGS__)); goto cleanup; }

void ReportError(char * fmtstr, ...);
