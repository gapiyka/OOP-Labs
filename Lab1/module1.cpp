﻿#include "pch.h"
#include "module1.h"

#pragma region VariablesAndFunctionsDeclarations

static int const maxSymbols = 255;
static char tempPlaceForText[maxSymbols] = { 0 };

int pos;
static int nMinPos = 1;
static int nMaxPos = 100;
static HWND hWndScrollBar_MOD1;
BOOL canWrite_MOD1 = FALSE;
int numOfDig_MOD1;

static INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

static void OnLineLeft(HWND hDlg);
static void OnLineRight(HWND hDlg);
static void OnClickOk(HWND hDlg);
static void OnClickCancel(HWND hDlg);
static void OnClose(HWND hDlg);
static void GetCurPos(HWND hDlg);

static void OnThumbPosAndTrack(HWND hDlg, WPARAM wParam);
static int CountDigits(int pos);

int Func_MOD1(HINSTANCE hInst, HWND hWnd, char *dest)
{
    return DialogBox(hInst , MAKEINTRESOURCE(IDD_WORK_MOD1), hWnd, Work1_MOD1);
    dest = tempPlaceForText;
}

INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        hWndScrollBar_MOD1 = GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD1);
        pos = 1;
        SetScrollRange(hWndScrollBar_MOD1, SB_CTL, nMinPos, nMaxPos, TRUE);
        break;
    case WM_HSCROLL:
        GetCurPos(hDlg);
        switch (LOWORD(wParam))
        {
        case SB_LINELEFT:
            OnLineLeft(hDlg);
            break;
        case SB_LINERIGHT:
            OnLineRight(hDlg);
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            OnThumbPosAndTrack(hDlg, wParam);
            break;
        default: break;
        }
        SetScrollPos(hWndScrollBar_MOD1, SB_CTL, pos, TRUE);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            OnClickOk(hDlg);
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            OnClickCancel(hDlg);
            return (INT_PTR)TRUE;
            break;
        }
        break;
    case WM_CLOSE:
    {
        OnClose(hDlg);
    }
    break;
    default: break;
    }
    return FALSE;
}

void OnLineLeft(HWND hDlg)
{
    if (pos != nMaxPos)
    {
        pos--;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
}

void OnLineRight(HWND hDlg)
{
    if (pos != nMaxPos)
    {
        pos++;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
}


void OnThumbPosAndTrack(HWND hDlg, WPARAM wParam)
{
    pos = HIWORD(wParam);
    SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
}

void OnClickOk(HWND hDlg)
{
    canWrite_MOD1 = TRUE;
    numOfDig_MOD1 = CountDigits(pos);
    EndDialog(hDlg, 1);
}


void OnClickCancel(HWND hDlg)
{
    EndDialog(hDlg, 0);
}

void OnClose(HWND hDlg)
{
    EndDialog(hDlg, 0);
}

void GetCurPos(HWND hDlg)
{
    pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD1), SB_CTL);
}

int CountDigits(int pos)
{
    int count_MOD1 = 0;
    while (pos != 0)
    {
        pos = pos / 10;
        ++count_MOD1;
    }
    return count_MOD1;
}