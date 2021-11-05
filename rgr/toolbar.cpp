#include "toolbar.h"


void Toolbar::NotifyText(LPTOOLTIPTEXT lpttt, LPCWSTR text) {
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
    openFile, saveFile, zoom, unzoom, hand, brightness, contrast, rgb, buttonToChange = 0;
    buttonToChange = id;
}

void Toolbar::OnToolOpenFile()
{
    OnNewTool(ID_TOOL_OPENFILE);
    openFile = !openFile;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OPENFILE, openFile);
}

void Toolbar::OnToolSaveFile()
{
    OnNewTool(ID_TOOL_SAVEFILE);
    saveFile = !saveFile;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_SAVEFILE, saveFile);
}

void Toolbar::OnToolZoom()
{
    OnNewTool(ID_TOOL_ZOOM);
    zoom = !zoom;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ZOOM, zoom);
}

void Toolbar::OnToolUnzoom()
{
    OnNewTool(ID_TOOL_UNZOOM);
    unzoom = !unzoom;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_UNZOOM, unzoom);
}

void Toolbar::OnToolHand()
{
    OnNewTool(ID_TOOL_HAND);
    hand = !hand;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_HAND, hand);
}

void Toolbar::OnToolBrightness()
{
    OnNewTool(ID_TOOL_BRIGHTNESS);
    brightness = !brightness;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_BRIGHTNESS, brightness);
}

void Toolbar::OnToolContrast()
{
    OnNewTool(ID_TOOL_CONTRAST);
    contrast = !contrast;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CONTRAST, contrast);
}

void Toolbar::OnToolRGB()
{
    OnNewTool(ID_TOOL_RGB);
    rgb = !rgb;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RGB, rgb);
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
            NotifyText(lpttt, L"Відкрити файл");
            break;
        case ID_TOOL_SAVEFILE:
            NotifyText(lpttt, L"Зберегти файл");
            break;
        case ID_TOOL_ZOOM:
            NotifyText(lpttt, L"Приблизити");
            break;
        case ID_TOOL_UNZOOM:
            NotifyText(lpttt, L"Віддалити");
            break;
        case ID_TOOL_HAND:
            NotifyText(lpttt, L"Переміщення");
            break;
        case ID_TOOL_BRIGHTNESS:
            NotifyText(lpttt, L"Яскравість");
            break;
        case ID_TOOL_CONTRAST:
            NotifyText(lpttt, L"Контрастність");
            break;
        case ID_TOOL_RGB:
            NotifyText(lpttt, L"Корекція RGB");
            break;
        default: NotifyText(lpttt, L"Щось не відоме");
        }
    }
}