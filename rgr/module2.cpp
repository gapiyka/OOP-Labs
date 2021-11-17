#include "module2.h"

static int pos;
static int nMinPos = 0;
static int nMaxPos = 200;
static const int defaultN = 100;
static HWND hWndScrollBar_MOD2;

static INT_PTR CALLBACK Work2_MOD2(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

static void OnLineLeft(HWND hDlg);
static void OnLineRight(HWND hDlg);
static void OnClickOk(HWND hDlg);
static void OnClickCancel(HWND hDlg);
static void OnClose(HWND hDlg);
static void GetCurPos(HWND hDlg);

static void OnThumbPosAndTrack(HWND hDlg, WPARAM wParam);

int Func_MOD2(HINSTANCE hInst, HWND hWnd, int* i)
{
    int res = DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD2), hWnd, Work2_MOD2);
    if (pos != defaultN) { *i = (pos - defaultN) * 2; }
    else { *i = 0; }
    return res;
}

INT_PTR CALLBACK Work2_MOD2(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        hWndScrollBar_MOD2 = GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD2);
        pos = defaultN;
        SetScrollRange(hWndScrollBar_MOD2, SB_CTL, nMinPos, nMaxPos, TRUE);
        SetScrollPos(hWndScrollBar_MOD2, SB_CTL, pos, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos-defaultN, TRUE);
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
        SetScrollPos(hWndScrollBar_MOD2, SB_CTL, pos, TRUE);
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
    if (pos != nMinPos)
    {
        pos--;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos - defaultN, TRUE);
}

void OnLineRight(HWND hDlg)
{
    if (pos != nMaxPos)
    {
        pos++;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos - defaultN, TRUE);
}


void OnThumbPosAndTrack(HWND hDlg, WPARAM wParam)
{
    pos = HIWORD(wParam);
    SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos - defaultN, TRUE);
}

void OnClickOk(HWND hDlg)
{
    EndDialog(hDlg, 1);
}


void OnClickCancel(HWND hDlg)
{
    pos = defaultN;
    EndDialog(hDlg, 0);
}

void OnClose(HWND hDlg)
{
    pos = defaultN;
    EndDialog(hDlg, 0);
}

void GetCurPos(HWND hDlg)
{
    pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD2), SB_CTL);
}