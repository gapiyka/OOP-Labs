#include "pch.h"
#include "module3.h"
#include "module2.h"
#include "Resource.h"

static void OnClickNext(HWND hDlg)
{
    EndDialog(hDlg, 1);

    Func_MOD3(hInst, hDlg);
}

static void OnClickCancel(HWND hDlg)
{
    EndDialog(hDlg, 0);
}

static void OnClickClose(HWND hDlg)
{
    EndDialog(hDlg, 0);
}

static INT_PTR CALLBACK Work_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CANCEL1_MOD2:
            OnClickCancel(hDlg);
            return (INT_PTR)TRUE;
        case IDC_NEXT_MOD2:
            OnClickNext(hDlg);
            return (INT_PTR)TRUE;
        }
        break;
    case WM_CLOSE:
    {
        OnClickClose(hDlg);
    }
    break;
    }
    return (INT_PTR)FALSE;
}

int Func_MOD2(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK1_MOD2), hWnd, Work_MOD2);
}
