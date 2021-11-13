#pragma once
#include "rgr.h"
#include "toolbar_resource.h"
#include "files.h"

class Toolbar
{
private:
	HWND hwndToolBar = NULL;
	int openFile, saveFile, zoom, unzoom, hand, brightness, contrast, rgb, buttonToChange = 0;
	int tools[TOOLS] = {	ID_TOOL_OPENFILE , ID_TOOL_SAVEFILE, ID_TOOL_ZOOM, ID_TOOL_UNZOOM,
							ID_TOOL_HAND, ID_TOOL_BRIGHTNESS, ID_TOOL_CONTRAST, ID_TOOL_RGB };
	void OnNewTool(int id);
	void NotifyText(LPTOOLTIPTEXT lpttt, LPCSTR text);
public:
	void OnSize(HWND hWnd);
	void OnCreate(HWND hWnd);
	void OnNotify(HWND hWnd, LPARAM lParam);
	void OnToolOpenFile(Viewer *viewer);
	void OnToolSaveFile();
	void OnToolZoom();
	void OnToolUnzoom();
	void OnToolHand();
	void OnToolBrightness();
	void OnToolContrast();
	void OnToolRGB();
};