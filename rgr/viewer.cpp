#include "viewer.h"

Viewer::Viewer() {
	hWnd = NULL;
	hInst = NULL;
	IsOpenedFile = 0;
}

void Viewer::resetScreen() {
	InvalidateRect(hWnd, NULL, TRUE);
}

void Viewer::setFile(char* name) {
	img_name = name;
	IsOpenedFile = 1;
	resetScreen();
}

void Viewer::Paint(HWND hwnd, HINSTANCE hinst)
{
	const int STARTY = 37;
	const int STARTX = 0;

	if (hWnd == NULL) {
		hWnd = hwnd;
		hInst = hinst;
	}

	PAINTSTRUCT		ps;
	HDC				hdc;
	hdc = BeginPaint(hWnd, &ps);

	if (IsOpenedFile == 1) {
		BITMAP          bitmap;
		HDC             hdcMem;
		HBITMAP         oldBitmap;
		CHAR			szBuffer[255];
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, img_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		BitBlt(hdc, STARTX, STARTY, STARTX+bitmap.bmWidth, STARTY + bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		DeleteObject(hBitmap);
	}
		
	

	EndPaint(hWnd, &ps);
}