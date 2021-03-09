// DrPepUr#4 Keygen
// 2008 andrewl

// OS
#define _WIN32_WINNT 0x0502
#include <windows.h>

// local stuff
#include ".\resource\myresource.h"

// local libs
#include "Executer.h"
#include "FunWindowsHelpers.h"

// globals
HICON g_hIcon=0;

// helper function for writing to crackme
BOOL memcpy2(PVOID dest, PVOID src, UINT num)
{
    BOOL bRet=0;

    DWORD dwOldProtect;
    DWORD dwNewProtect=PAGE_READWRITE;

    if(!VirtualProtect(dest, num, dwNewProtect, &dwOldProtect))
     { ReportError("VirtualProtect"); goto cleanup; }

    memcpy(dest, src, num);

    if(!VirtualProtect(dest, num, dwOldProtect, &dwNewProtect))
     { ReportError("VirtualProtect"); goto cleanup; }

    bRet=1;

    cleanup:

    return bRet;
}

// generates key
VOID DoKey(HWND hWnd)
{
    char buff[256]={0};

    GetDlgItemText(hWnd, ID_EDIT2, buff, 256);

    if(strlen(buff) < 5)
        SetDlgItemText(hWnd, ID_EDIT1, "minimum 5 characters");
    else
    {
        // the TLS can get tricky... just the act of creating a thread (which the
        // instantiation of Executer does) will run the TLS, changing the data in
        // the crackme
        if(*(PBYTE)0x00403210 == 0x10)
            Executer e;

        if(*(PBYTE)0x00403210 != 0x55)
            MessageBoxA(0, "WTF!", "WTF!", 0);

        memcpy2((PVOID)0x403C62, "\xC3", 1); // prevent further execution of TLS

        Executer e;
        e.Setup(0x401A3C);
        strcpy((PCHAR)0x403704, buff);
        e.RunUntil(0x401A53);
        strcpy(buff, "DRP-");
        strncpy(buff+4, (PCHAR)0x40376C, 32);
        SetDlgItemText(hWnd, ID_EDIT1, buff);
    }
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    BOOL    bProcessedMessage = TRUE;

    switch(Message) 
    {
            case WM_INITDIALOG:
                {
                    char buff[512]={0};
                    DWORD dwRet;
                    if(GetComputerName(buff, &dwRet))
                    {
                        while(strlen(buff)<5)
                            strcat(buff, "1");

                        for(int i=0; i<strlen(buff); ++i)
                            buff[i] = tolower(buff[i]);
                        
                        SetDlgItemText(hWnd, ID_EDIT2, buff);
                    }
                
                    SendMessage(GetDlgItem(hWnd, ID_EDIT1), EM_SETREADONLY, (WPARAM)1, (LPARAM)0);
                    CenterWindow(hWnd);
                    DoKey(hWnd);
                }

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

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    return TRUE;
}

extern "C" __declspec(dllexport) void KGEntry()
{
    HMODULE hModule;
    GetModuleHandleEx(2, "keygen", &hModule);
    g_hIcon = (HICON)LoadImage(hModule, MAKEINTRESOURCE(ID_ICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
    DialogBox(hModule, MAKEINTRESOURCE(ID_DIALOG), NULL, DlgProc);
    DestroyIcon(g_hIcon);
    ExitProcess(0);
}

