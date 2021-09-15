#include "pch.h"
#include "module3.h"

static INT_PTR CALLBACK Work2_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_OK2_MOD2:
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
        case IDC_CANCEL2_MOD2:
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        case IDC_BACK_MOD2:
            EndDialog(hDlg, -1);
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

int Func_MOD3(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK2_MOD2), hWnd, Work2_MOD2);
}