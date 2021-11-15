#include "framework.h"
#include "scrollbar.h"
#include <vector>

class Viewer
{
private:
	HWND		hWnd;
	HINSTANCE	hInst;
	HDC			hdc;
	Scrollbar	scrollbar;
	void resetScreen();
	char* img_name;
	int IsOpenedFile;
	int img_width;
	int img_height;
	int scrollX;
	int scrollY;
	float zoom;
	const int STARTY = 37;
	const int STARTX = 0;
	vector<COLORREF> pixelMatrix;
	int x1;
	int y1;
	int x2;
	int y2;
	BOOL isPressed = false;
	int isMoveTool;
public:
	Viewer();
	void Paint(HWND hwnd, HINSTANCE hinst);
	void setFile(char* name);
	void loadFile(HDC hdc);
	void saveScreenRGB(HDC hdc);
	void outputScreenRGB(HDC hdc);
	void zoomHDC();
	void unzoomHDC();
	void setScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void setScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnLMBDown(HWND hWnd);
	void OnLMBUp(HWND hWnd);
	void OnMouseMove(HWND hWnd);
	void moveTool(int is);
};