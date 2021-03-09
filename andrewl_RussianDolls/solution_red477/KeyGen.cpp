
#include <windows.h>
#include "resource.h"

#ifndef _DEBUG

#pragma comment(linker,"/ENTRY:WinMain")
#pragma comment(linker,"/OPT:NOWIN98")

#endif
void GetKey(HWND hWnd)
{
	TCHAR k[8][2]={
		{'1','C'},
		{'R','4'},
		{'a','2'},
		{'8','C'},
		{'5','k'},
		{'7','M'},
		{'E','1'},
		{'s','4'}
	};
	TCHAR szKey[9];

	szKey[0]=k[0][GetTickCount()%2];Sleep(10);

	szKey[1]=k[1][GetTickCount()%2];Sleep(10);

	szKey[2]=k[2][GetTickCount()%2];Sleep(10);

	szKey[3]=k[3][GetTickCount()%2];Sleep(10);

	szKey[4]=k[4][GetTickCount()%2];Sleep(10);

	szKey[5]=k[5][GetTickCount()%2];Sleep(10);

	szKey[6]=k[6][GetTickCount()%2];Sleep(10);

	szKey[7]=k[7][GetTickCount()%2];Sleep(10);

	szKey[8]='\0';

	SetDlgItemText(hWnd,IDC_EDTKEY,(LPCTSTR)szKey);
}
HINSTANCE hInst;

INT_PTR CALLBACK DialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
	switch(uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTNEXIT:
			SendMessage(hwndDlg,WM_CLOSE,NULL,NULL);
			break;
		case IDC_BTNKEY:
			GetKey(hwndDlg);
			break;
		}
		break;
	case WM_INITDIALOG:
		GetKey(hwndDlg);
		break;
	case WM_RBUTTONUP:
		SendMessage(hwndDlg,WM_CLOSE,NULL,NULL);
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,NULL);
		break;
	case WM_LBUTTONDOWN:
		ReleaseCapture();
		SendMessage(hwndDlg,WM_NCLBUTTONDOWN,HTCAPTION,NULL);
		break;

	default:
		return FALSE;
	}
	return TRUE;
}
int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
)
{
	hInst=GetModuleHandle(NULL);
	DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_KEYGEN),NULL,(DLGPROC)DialogProc,NULL);
	return TRUE;
}