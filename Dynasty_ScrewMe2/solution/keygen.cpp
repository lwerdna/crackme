#define _WIN32_WINNT 0x0502
#include <windows.h>
#include <Commdlg.h>

#include "myresource.h"

// globals
char g_buffer[MAX_PATH];

unsigned int g_sum;
unsigned int g_sum_12;
int i;
DWORD dwRet;

// fucking visual studio can't decide if it
// wants to use intrinsics or not
void * memset(void *s, int c, size_t n)
{
    __asm
    {
        pushad
        mov     al, byte ptr[c]
        mov     ecx, dword ptr[n]
        mov     edi, dword ptr[s]
        rep     stosb;
        popad
    }
    
    return s;
}

extern "C" void * memcpy(void *d, const void * s, size_t n)
{
    __asm
    {
        pushad
        mov     esi, dword ptr[s]
        mov     edi, dword ptr[d]
        mov     ecx, dword ptr[n]
        rep     movsb
        popad
    }

    return d;
}

// 
void reportError(TCHAR * msg)
{
	char errorString[256];
    char skipAhead = 0;

    wsprintfA(errorString, "error: %s\n", msg);

    skipAhead = lstrlenA(errorString);

	FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        			NULL,
		        	GetLastError(),
        			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        			errorString + skipAhead,
        			512-skipAhead,
        			0
    		     );

    MessageBoxA(NULL, errorString, "error", NULL);
}

BOOL CALLBACK MyDialogProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    BOOL    bProcessedMessage = TRUE;

    switch(Message) {
            case WM_INITDIALOG:
                SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, IDI_WARNING));
                SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, IDI_WARNING));
                bProcessedMessage=TRUE;
                break;
            case WM_CLOSE:
                EndDialog(hWnd, IDOK);
                break;
            case WM_COMMAND:
                switch(HIWORD(wParam)) {
                    case EN_CHANGE:
                        if(LOWORD(wParam) == ID_EDIT1)
                        {
                            g_sum = g_sum_12 = 0;
                            
                            GetDlgItemText(hWnd, ID_EDIT1, g_buffer, MAX_PATH);
                            int len=lstrlenA(g_buffer);

                            if(len>8)
                                SetDlgItemText(hWnd, ID_EDIT2, "too big");
                            else
                            {
                                for(int i=0; i<len; ++i)
                                    g_sum+=g_buffer[i];

                                g_sum_12 = g_sum * 12;
                                wsprintfA(g_buffer, "%d-Dyn", g_sum_12);
                                SetDlgItemText(hWnd, ID_EDIT2, g_buffer);
                            }
                        }

                        break;
                    
                    case BN_CLICKED:
                    {
                        if(LOWORD(wParam) == ID_BUTTON1) {
                            // get serial
                            GetDlgItemText(hWnd, ID_EDIT2, g_buffer, MAX_PATH);

                            // if the serial is not generated, quit
                            if(!g_sum)
                                { MessageBoxA(NULL, "generate valid key first", "error", MB_OK); break; }

                            int len = lstrlenA(g_buffer);

                            // have user pick location of key file
                            lstrcatA(g_buffer, ".nob");

                            OPENFILENAME ofn;
                            memset(&ofn, 0, sizeof(ofn));
                            ofn.hwndOwner=hWnd;
                            ofn.lStructSize=sizeof(OPENFILENAME);
                            ofn.lpstrFile=g_buffer;
                            ofn.nMaxFile=MAX_PATH-1;
                            ofn.lpstrTitle="save this file next to the crackme";
                            ofn.lpstrFile=g_buffer;

                            if(!GetSaveFileName(&ofn))
                                { reportError("didn't specify key file"); break; }



                            // open the file
                            HANDLE hFile;
                            if(INVALID_HANDLE_VALUE==(hFile=CreateFile(ofn.lpstrFile, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, 0)))
                                { reportError("opening file"); break; }

                            // calculate key file contents

                            memset(g_buffer, 0, MAX_PATH);
                            memset(g_buffer, 1, len*2);

                            for(i=0; i < g_sum-len; ++i)
                                { g_buffer[2*(i%len)]=0x31; ++g_buffer[2*(i%len)+1]; }

                            lstrcatA(g_buffer, "\x30\xCC\x30\xCC\x30\xCC\x30\xCC"
                                                "\x30\xCC\x30\xCC\x30\xCC\x30\xCC"
                                                "\x30\xCC\x30\xCC\x30\xCC\x30\xCC"
                                                "\x30\xCC\x30\xCC\x30\xCC\x30\xCC");

                            // write the file out
                            if(!WriteFile(hFile, g_buffer, 2*len+32, &dwRet, 0))
                                { reportError("writing file"); break; }

                            CloseHandle(hFile);

                            break;
                        }
                        
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
    DialogBox(hModule, MAKEINTRESOURCE(ID_DIALOG), NULL, MyDialogProc);
    ExitProcess(0);
}
