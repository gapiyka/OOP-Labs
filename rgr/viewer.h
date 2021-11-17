#include "framework.h"
#include "scrollbar.h"
#include "module1.h"
#include "module2.h"
#include "module3.h"
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
	const int STARTY = 37;
	const int STARTX = 0;
	int IsOpenedFile;
	int img_width;
	int img_height;
	int scrollX;
	int scrollY;
	int isMoveTool;
	int x1;
	int y1;
	int x2;
	int y2;
	float zoom;
	BOOL isPressed;
	vector<COLORREF> pixelMatrix;
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
	void brightnessChange();
	void contrastChange();
	void rgbChange();
};