#include "toolbar.h"

Files files;

void Toolbar::NotifyText(LPTOOLTIPTEXT lpttt, LPCSTR text) {
    lstrcpy(lpttt->szText, text);
}

void Toolbar::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[TOOLS+1];
    ZeroMemory(tbb, sizeof(tbb));
    for (int i = 0; i < TOOLS; i++) {
        tbb[i].iBitmap = i;
        tbb[i].fsState = TBSTATE_ENABLED;
        tbb[i].fsStyle = TBSTYLE_BUTTON;
        tbb[i].idCommand = tools[i];
    }

    tbb[TOOLS].iBitmap = TOOLS;
    tbb[TOOLS].fsState = TBSTATE_ENABLED;
    tbb[TOOLS].fsStyle = TBSTYLE_SEP;
    tbb[TOOLS].idCommand = 0;

    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        TOOLS,
        hInst,
        IDB_BITMAP1,
        tbb,
        TOOLS+1,
        24, 24, 24, 24,
        sizeof(TBBUTTON));
}

void Toolbar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc);
        GetWindowRect(hwndToolBar, &rw);
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void Toolbar::OnToolOpenFile(Viewer *viewer)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OPENFILE, 1);
    files.OpenFile(viewer);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OPENFILE, 0);
}

void Toolbar::OnToolSaveFile(Viewer *viewer)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_SAVEFILE, 1);
    files.SaveFile(viewer);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_SAVEFILE, 0);
}

void Toolbar::OnToolZoom(Viewer *viewer)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ZOOM, 1);
    viewer->zoomHDC();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ZOOM, 0);
}

void Toolbar::OnToolUnzoom(Viewer* viewer)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_UNZOOM, 1);
    viewer->unzoomHDC();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_UNZOOM, 0);
}

void Toolbar::OnToolHand(Viewer* viewer)
{
    IsMovePressed = !IsMovePressed;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_HAND, IsMovePressed);
    viewer->moveTool(IsMovePressed);
}

void Toolbar::OnToolBrightness()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_BRIGHTNESS, 1);
    //
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_BRIGHTNESS, 0);
}

void Toolbar::OnToolContrast()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CONTRAST, 1);
    //
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CONTRAST, 0);
}

void Toolbar::OnToolRGB()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RGB, 1);
    //
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RGB, 0);
}

void Toolbar::OnNotify(HWND hWnd, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    LPCSTR pText;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_OPENFILE:
            NotifyText(lpttt, "³������ ����");
            break;
        case ID_TOOL_SAVEFILE:
            NotifyText(lpttt, "�������� ����");
            break;
        case ID_TOOL_ZOOM:
            NotifyText(lpttt, "����������");
            break;
        case ID_TOOL_UNZOOM:
            NotifyText(lpttt, "³�������");
            break;
        case ID_TOOL_HAND:
            NotifyText(lpttt, "����������");
            break;
        case ID_TOOL_BRIGHTNESS:
            NotifyText(lpttt, "���������");
            break;
        case ID_TOOL_CONTRAST:
            NotifyText(lpttt, "�������������");
            break;
        case ID_TOOL_RGB:
            NotifyText(lpttt, "�������� RGB");
            break;
        default: NotifyText(lpttt, "���� �� �����");
        }
    }
}