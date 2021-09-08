#include "pch.h"
#include "framework.h"
#include "module3.h"
#include "module2.h"
#include "Resource.h"

static void OnClickBack(HWND hDlg)
{
    EndDialog(hDlg, -1);
    Func_MOD2(hInst, hDlg);
}

static void OnClickOk(HWND hDlg)
{
    EndDialog(hDlg, 1);
}

static void OnClickCancel(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    EndDialog(hDlg, 0);
    DefWindowProc(hDlg, message, wParam, lParam);
}

static INT_PTR CALLBACK Work2_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_OK2_MOD2:
            OnClickOk(hDlg);
            return (INT_PTR)TRUE;
        case IDC_CANCEL2_MOD2:
            OnClickCancel(hDlg, message, wParam, lParam);
            return (INT_PTR)TRUE;
        case IDC_BACK_MOD2:
            OnClickBack(hDlg);
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