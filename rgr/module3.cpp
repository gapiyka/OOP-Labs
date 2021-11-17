#include "module3.h"
#include <stdio.h>

static int posR, posG, posB, pressedRBut, pressedGBut, pressedBBut;
static int nMinpos = 0;
static int nMaxpos = 510;
static const int defaultN = 255;
static HWND hWndScrollBar1_MOD3;

static INT_PTR CALLBACK Work3_MOD3(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

static void OnLineLeft(HWND hDlg);
static void OnLineRight(HWND hDlg);
static void OnClickOk(HWND hDlg);
static void OnClickCancel(HWND hDlg);
static void OnClose(HWND hDlg);
static void GetCurPos(HWND hDlg, WPARAM wParam);
static void PrintCurPos(HWND hDlg);
static void SetCurPos(int pos);
static void OnRedButton(HWND hDlg);
static void OnGreenButton(HWND hDlg);
static void OnBlueButton(HWND hDlg);
static int checkButton();

int Func_MOD3(HINSTANCE hInst, HWND hWnd, int* r, int* g, int* b)
{
    int res = DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD3), hWnd, Work3_MOD3);
    if (posR != defaultN) { *r = (posR - defaultN); }
    else { *r = 0; }
    if (posG != defaultN) { *g = (posG - defaultN); }
    else { *g = 0; }
    if (posB != defaultN) { *b = (posB - defaultN); }
    else { *b = 0; }
    return res;
}

INT_PTR CALLBACK Work3_MOD3(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        hWndScrollBar1_MOD3 = GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD3);
        posR = defaultN;
        posG = defaultN;
        posB = defaultN;
        SetScrollRange(hWndScrollBar1_MOD3, SB_CTL, nMinpos, nMaxpos, TRUE);
        PrintCurPos(hDlg);
        break;
    case WM_HSCROLL:
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
            GetCurPos(hDlg, wParam);
            break;
        default: break;
        }
        PrintCurPos(hDlg);
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
        case IDRED:
            OnRedButton(hDlg);
            break;
        case IDGREEN:
            OnGreenButton(hDlg);
            break;
        case IDBLUE:
            OnBlueButton(hDlg);
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
    if (posR != nMinpos && pressedRBut)
    {
        posR--;
    }
    if (posG != nMinpos && pressedGBut)
    {
        posG--;
    }
    if (posB != nMinpos && pressedBBut)
    {
        posB--;
    }
}

void OnLineRight(HWND hDlg)
{
    if (posR != nMaxpos && pressedRBut)
    {
        posR++;
    }
    if (posG != nMaxpos && pressedGBut)
    {
        posG++;
    }
    if (posB != nMaxpos && pressedBBut)
    {
        posB++;
    }
}

void OnClickOk(HWND hDlg)
{
    EndDialog(hDlg, 1);
}


void OnClickCancel(HWND hDlg)
{
    posR = defaultN;
    posG = defaultN;
    posB = defaultN;
    EndDialog(hDlg, 0);
}

void OnClose(HWND hDlg)
{
    posR = defaultN;
    posG = defaultN;
    posB = defaultN;
    EndDialog(hDlg, 0);
}

void GetCurPos(HWND hDlg, WPARAM wParam)
{
    int pos = HIWORD(wParam);
    if (pressedRBut) posR = pos;
    if (pressedGBut) posG = pos;
    if (pressedBBut) posB = pos;
}


void SetCurPos(int pos)
{
    SetScrollPos(hWndScrollBar1_MOD3, SB_CTL, pos, TRUE);
}

void PrintCurPos(HWND hDlg)
{
    int pos = checkButton();
    SetDlgItemInt(hDlg, IDC_STATIC_MOD3, pos - defaultN, TRUE);
    SetCurPos(pos);
}

void OnRedButton(HWND hDlg) {
    pressedGBut = pressedBBut = 0;
    pressedRBut = 1;
    SetDlgItemText(hDlg, ID3_TEXT3, "Червоний:");
    PrintCurPos(hDlg);
}

void OnGreenButton(HWND hDlg) {
    pressedRBut = pressedBBut = 0;
    pressedGBut = 1;
    SetDlgItemText(hDlg, ID3_TEXT3, "Зелений:");
    PrintCurPos(hDlg);
}

void OnBlueButton(HWND hDlg) {
    pressedGBut = pressedRBut = 0;
    pressedBBut = 1;
    SetDlgItemText(hDlg, ID3_TEXT3, "Синій:");
    PrintCurPos(hDlg);
}

int checkButton() {
    if (pressedRBut) return posR;
    if (pressedGBut) return posG;
    if (pressedBBut) return posB;
    return defaultN;
}