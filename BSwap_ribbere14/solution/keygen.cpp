// Ribbere 1.4 keygen
// 2008 andrewl

// OS
#define _WIN32_WINNT 0x0502
#include <windows.h>

// local stuff
#include ".\resource\myresource.h"

// local libs
#include "funwindowshelpers.h"

// globals
HICON g_hIcon=0;

ULONG rand_a=1664525;
ULONG rand_c=1013904223;
ULONG rand_Xn=0;

ULONG myrand()
{
    while(rand_Xn==0)
    {
        __asm
        {
            rdtsc
            mov [rand_Xn], eax
        }
    }

    rand_Xn = rand_a * rand_Xn + rand_c; // (mod 2^32)

    return rand_Xn;
}

VOID DoKey(HWND hWnd)
{
    #define RANDOM_CHAR (myrand()%91+32) // 4 short, so +4 will be valid

    CHAR    buff[13];
    DWORD   dwRet;

    for(UINT i=0; i<12; ++i)
        buff[i] = RANDOM_CHAR;

    buff[12]=0;

    *(PULONG)(buff+5) = *(PULONG)(buff+1) + 0x04040404;

    SetDlgItemText(hWnd, ID_EDIT1, buff);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    BOOL    bProcessedMessage = TRUE;

    switch(Message) 
    {
            case WM_INITDIALOG:
                if(g_hIcon)
                {
                    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)g_hIcon);
                    SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)g_hIcon);
                    SendMessage(hWnd, WM_SETICON, ICON_SMALL2, (LPARAM)g_hIcon);
                }
                
                SendMessage(GetDlgItem(hWnd, ID_EDIT1), EM_SETREADONLY, (WPARAM)1, (LPARAM)0);
                CenterWindow(hWnd);
                DoKey(hWnd);
                break;

            case WM_CLOSE:
                EndDialog(hWnd, IDOK);
                break;

            case WM_COMMAND:
                if(LOWORD(wParam) == IDCANCEL)
                {
                    SendMessage(hWnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                    break;
                }

                switch(HIWORD(wParam))
                {

                    case BN_CLICKED:
                    {
                        if(LOWORD(wParam) == ID_BUTTON1) 
                            DoKey(hWnd);
                        
                        break;
                    }

                    default:
                        bProcessedMessage=FALSE;
                        break;
                }

            default:
                bProcessedMessage=FALSE;
                break;
    }

    return bProcessedMessage;
}

void MyEntry() {
    HMODULE hModule;
    GetModuleHandleEx(2, NULL, &hModule);
    g_hIcon = (HICON)LoadImage(hModule, MAKEINTRESOURCE(ID_ICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
    DialogBox(hModule, MAKEINTRESOURCE(ID_DIALOG), NULL, DlgProc);
    DestroyIcon(g_hIcon);
    ExitProcess(0);
}

