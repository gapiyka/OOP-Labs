#include "toolbar.h"

Files files;

void Toolbar::NotifyText(LPTOOLTIPTEXT lpttt, LPCSTR text) {
    lstrcpy(lpttt->szText, text);
}

void Toolbar::OnCreate(HWND hWnd)
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

void Toolbar::OnNewTool(int id) {
    SendMessage(hwndToolBar, TB_PRESSBUTTON, buttonToChange, 0);
    buttonToChange = id;

    SendMessage(hwndToolBar, TB_PRESSBUTTON, buttonToChange, 1);
}

void Toolbar::OnToolOpenFile(Viewer *viewer)
{
    OnNewTool(ID_TOOL_OPENFILE);
    files.OpenFile(viewer);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OPENFILE, 0);
}

void Toolbar::OnToolSaveFile()
{
    OnNewTool(ID_TOOL_SAVEFILE);
}

void Toolbar::OnToolZoom()
{
    OnNewTool(ID_TOOL_ZOOM);
}

void Toolbar::OnToolUnzoom()
{
    OnNewTool(ID_TOOL_UNZOOM);
}

void Toolbar::OnToolHand()
{
    OnNewTool(ID_TOOL_HAND);
}

void Toolbar::OnToolBrightness()
{
    OnNewTool(ID_TOOL_BRIGHTNESS);
}

void Toolbar::OnToolContrast()
{
    OnNewTool(ID_TOOL_CONTRAST);
}

void Toolbar::OnToolRGB()
{
    OnNewTool(ID_TOOL_RGB);
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
            NotifyText(lpttt, "Відкрити файл");
            break;
        case ID_TOOL_SAVEFILE:
            NotifyText(lpttt, "Зберегти файл");
            break;
        case ID_TOOL_ZOOM:
            NotifyText(lpttt, "Приблизити");
            break;
        case ID_TOOL_UNZOOM:
            NotifyText(lpttt, "Віддалити");
            break;
        case ID_TOOL_HAND:
            NotifyText(lpttt, "Переміщення");
            break;
        case ID_TOOL_BRIGHTNESS:
            NotifyText(lpttt, "Яскравість");
            break;
        case ID_TOOL_CONTRAST:
            NotifyText(lpttt, "Контрастність");
            break;
        case ID_TOOL_RGB:
            NotifyText(lpttt, "Корекція RGB");
            break;
        default: NotifyText(lpttt, "Щось не відоме");
        }
    }
}