#include "framework.h"

class Viewer
{
private:
	HWND hWnd;
	HINSTANCE hInst;
	void resetScreen();
	char* img_name;
	int IsOpenedFile;
public:
	Viewer();
	void Paint(HWND hwnd, HINSTANCE hinst);
	void setFile(char* name);
};