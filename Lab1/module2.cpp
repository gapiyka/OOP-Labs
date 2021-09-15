#include "pch.h"
#include "module2.h"

static INT_PTR CALLBACK Work_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CANCEL1_MOD2:
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        case IDC_NEXT_MOD2:
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
        }
        break;
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
    }
    break;
    }
    return (INT_PTR)FALSE;
}

int Func_MOD2(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK1_MOD2), hWnd, Work_MOD2);
}
