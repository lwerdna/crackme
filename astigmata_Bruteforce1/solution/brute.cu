// 2008 andrewl

#undef TIMESHIT
//#define TIMESHIT 1

#include <windows.h>

#include <stdio.h>

#include <cuda.h>

typedef struct _STATE
{
    DWORD eax;
    DWORD ebx;
    CHAR CF;
} STATE, *PSTATE;

__global__ void bruter(STATE *a, int N)
{
    int idx;
    ULONG i;
    ULONG shamt;
    ULONG temp;

    idx = blockIdx.x*blockDim.x + threadIdx.x;

//    if(idx < N)
//    {
    ULONG eax = a[idx].eax;
    ULONG ebx = a[idx].ebx;
    UCHAR CF = a[idx].CF;

    for(i=0; i<4000000; ++i)
    {
        // emulate RCR EAX, AL

        shamt = eax & 0x1F;

        if(shamt)
        {
            ULONG left = 0, right, ceffect;

            right = eax >> shamt;

            shamt = 32 - shamt;
            ceffect = CF << shamt;

            if(++shamt < 32)
                left = eax << shamt;

            eax = left | ceffect | right;          
        }

        eax += ebx;
        eax += 0x11223344;

        CF = 0;
        if(eax < 0x11223344)
            CF = 1;

        temp = eax;
        eax = ebx;
        ebx = temp;
    }

    a[idx].eax = eax;
    a[idx].ebx = ebx;
    a[idx].CF = CF;
//    }
}

UCHAR g_trial_digits[8]={0};

__forceinline DWORD next_eax()
{
    // ugly, but for speed

    DWORD ret =     g_trial_digits[0] |
                    (g_trial_digits[1] << 4) |
                    (g_trial_digits[2] << 8) |
                    (g_trial_digits[3] << 12) |
                    (g_trial_digits[4] << 16) |
                    (g_trial_digits[5] << 20) |
                    (g_trial_digits[6] << 24) |
                    (g_trial_digits[7] << 28);

    g_trial_digits[0]++;
    if(g_trial_digits[0] <= 9)
        return ret;
    g_trial_digits[0] = 0;
    g_trial_digits[1]++;
    if(g_trial_digits[1] <= 9)
        return ret;
    g_trial_digits[1] = 0;
    g_trial_digits[2]++;
    if(g_trial_digits[2] <= 9)
        return ret;
    g_trial_digits[2] = 0;
    g_trial_digits[3]++;
    if(g_trial_digits[3] <= 9)
        return ret;
    g_trial_digits[3] = 0;
    g_trial_digits[4]++;
    if(g_trial_digits[4] <= 9)
        return ret;
    g_trial_digits[4] = 0;
    g_trial_digits[5]++;
     if(g_trial_digits[5] <= 9)
        return ret;
    g_trial_digits[5] = 0;
    g_trial_digits[6]++;
    if(g_trial_digits[6] <= 9)
        return ret;
    g_trial_digits[6] = 0;
    g_trial_digits[7]++;
    if(g_trial_digits[7] <= 9)
        return ret;
    g_trial_digits[7] = 0; // around the corner!
    return ret;
}

unsigned __int64 hexStrToUint64(const char * hex_string)
{
    unsigned __int64 result = 0;
    int len=0, i=0;
    unsigned char value;

    if(hex_string[0]=='0' && hex_string[1]=='x')
        hex_string += 2;

    // find strlen
    len=-1;
    while(hex_string[++len]!='\0');

    if(len > 8)
        return 0xFFFFFFFF;

    for(i=0; i<len; i++) {
        char temp = hex_string[i];

        if((temp>=0x30) && (temp <=0x39)) // [0-9]
            value = temp - 0x30;
        else if(temp>=0x41 && temp<=0x46) // [A-F]
            value = temp - 0x37;
        else if(temp>=0x61 && temp<=0x66) // [A-Fa-f]
            value = temp - 0x57;
        else
            return 0xFFFFFFFF;

        result = result | (ULONG)(value << ((len-i-1) * 4));
    }

    return result;
}

void print_state(STATE s)
{
    printf("{0x%08X,0x%08X,%d}", s.eax, s.ebx, s.CF);
}

HANDLE g_hEvent0 = 0; // thread signals that he is alive
HANDLE g_hEvent1 = 0; // main signals that status message is awaiting
HANDLE g_hThread = 0;
CHAR g_LastStatusMessage[256];

DWORD WINAPI StatusReporter(LPVOID param)
{
    CHAR urlbuff[512];

    SetEvent(g_hEvent0);

    while(1)
    {
        printf("THREAD: waiting for work to report...\n");

        WaitForSingleObject(g_hEvent1, INFINITE);

        printf("THREAD: uploading message: %s\n", g_LastStatusMessage);

        sprintf(urlbuff, "http://andrewl.us/astigmata/?liwfEIJFkefji3=%s", g_LastStatusMessage);

        if(URLDownloadToFileA(0, urlbuff, "c:\\temp.txt", 0, 0) != S_OK)
            printf("THREAD: fuck man, upload failed!\n");
    }
}


int main(int argc, char * argv[])
{
    #define BLOCKSIZE 512
    #define NBLOCKS 24
    #define BATCHSIZE (BLOCKSIZE*NBLOCKS)

    // time measurement stuff
    #ifdef TIMESHIT
    FILETIME t0, t1;
    ULONGLONG s1;
    ULONGLONG s0;
    ULONGLONG diff;
    float difff;
    #endif

    // other vars
    cudaError_t err;

    // memories
    PSTATE trials_host = 0; 
    PSTATE trials_device = 0;
    PSTATE results = 0;

    // parse args
    if(argc > 1)
    {
        ULONG init = hexStrToUint64(argv[1]);
    
        for(int i=0; i<8; ++i)
            g_trial_digits[i] = ((0x0F << (4*i)) & init) >> (4*i);
    }

    size_t size = BATCHSIZE * sizeof(STATE);

    // create event to signal thread
    g_hEvent0 = CreateEvent(0, 0, 0, 0); // no security, auto-reset, initially 0, no name
    g_hEvent1 = CreateEvent(0, 0, 0, 0); // no security, auto-reset, initially 0, no name
    HANDLE g_hThread = CreateThread(0, 0, StatusReporter, 0, 0, 0);
    WaitForSingleObject(g_hEvent0, INFINITE);

    // allocate arrays on host
    trials_host = (PSTATE)malloc(size);
    memset(trials_host, 0, size);
    results = (PSTATE)malloc(size);

    // allocate array on device 
    err = cudaMalloc((PVOID *)&trials_device, size);
    if(err != cudaSuccess)
        goto cleanup;

    while(1)
    {
        for(int i=0; i<BATCHSIZE; i++) 
            trials_host[i].eax = next_eax();

        //
        // signal thread to upload results
        //
        sprintf(    g_LastStatusMessage,
                    "searching [%08X, %08X]",
                    trials_host[0].eax, 
                    trials_host[BATCHSIZE-1].eax
                );

        SetEvent(g_hEvent1);

        // copy data from host to device
        err = cudaMemcpy(trials_device, trials_host, size, cudaMemcpyHostToDevice);
        if(err != cudaSuccess)
            goto cleanup;

        #ifdef TIMESHIT
        GetSystemTimeAsFileTime(&t0);
        #endif

        for(INT i=0; i<25; ++i)
        {
            bruter <<< NBLOCKS, BLOCKSIZE >>> ((PSTATE)trials_device, BATCHSIZE);
   
            err = cudaThreadSynchronize();
            if(err != cudaSuccess)
                goto cleanup;
            
            printf("called kernel %d\r", i);
        }

        err = cudaMemcpy(results, trials_device, size, cudaMemcpyDeviceToHost);
        if(err != cudaSuccess)
            goto cleanup;

        #ifdef TIMESHIT
        GetSystemTimeAsFileTime(&t1);
        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        #endif

        // check results
        for (INT i=0; i<BATCHSIZE; i++)
        {
            /*
            printf("result: ");
            print_state(trials_host[i]);
            printf("->");
            print_state(results[i]);
            printf("\n");
            */

            if((results[i].eax ^ results[i].ebx) == 0xD5446474 )
            //if((results[i].eax ^ results[i].ebx) == 0xd3c7896e )
            {
                sprintf(    g_LastStatusMessage,
                            "!!! answer: 0x%08X",
                            trials_host[i].eax
                       );

                SetEvent(g_hEvent1);

                printf(g_LastStatusMessage);

                Sleep(0xFFFFFFFF);

                goto cleanup;
            }
        }

        #ifdef TIMESHIT
        printf("batch took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)BATCHSIZE);
        #endif
    }

    cleanup:

    if(err != cudaSuccess)
        printf("err: %s\n", cudaGetErrorString(err));

    if(g_hThread)
        CloseHandle(g_hThread);

    if(g_hEvent0)
        CloseHandle(g_hEvent0);

    if(g_hEvent1)
        CloseHandle(g_hEvent1);

    if(trials_host)
        free(trials_host);

    if(trials_device)
        cudaFree(trials_device); 
}

