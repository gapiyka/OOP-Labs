#include "viewer.h"

Viewer::Viewer() {
	hWnd = NULL;
	hInst = NULL;
	IsOpenedFile = 0;
	zoom = 1;
	scrollX = 0;
	scrollY = 0;
	isMoveTool = 0;
}

void Viewer::resetScreen() {
	InvalidateRect(hWnd, NULL, TRUE);
}

void Viewer::setFile(char* name) {
	img_name = name;
	IsOpenedFile = 1;
	resetScreen();
}

void Viewer::loadFile(HDC hdc) {
	BITMAP          bitmap;
	HDC             hdcMem;
	HBITMAP			oldBitmap;
	HBITMAP			hBitmap;
	hBitmap = (HBITMAP)LoadImage(NULL, img_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	img_width = bitmap.bmWidth;
	img_height = bitmap.bmHeight;
	BitBlt(hdc, STARTX, STARTY, STARTX + img_width, STARTY + img_height, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
	scrollbar.OnNewBmp(hWnd, img_width, img_height);
}

void Viewer::Paint(HWND hwnd, HINSTANCE hinst)
{
	if (hWnd == NULL) {
		hWnd = hwnd;
		hInst = hinst;
	}

	PAINTSTRUCT		ps;
	
	hdc = BeginPaint(hWnd, &ps);

	if (IsOpenedFile == 1) {
		loadFile(hdc);
		saveScreenRGB(hdc);
		IsOpenedFile = 0;
	}
	else {
		outputScreenRGB(hdc);
		StretchBlt(hdc, STARTX, STARTY, STARTX + img_width * zoom, STARTY + img_height * zoom,
			hdc, STARTX, STARTY, STARTX + img_width, STARTY + img_height, SRCCOPY);
		 
	}

	EndPaint(hWnd, &ps);
}

void Viewer::saveScreenRGB(HDC hdc)
{
	int counter = 0;
	if (img_width >= 0 && img_height >= 0) {
		pixelMatrix.resize(img_width * img_height + 1);
		for (int y = 0; y < img_height; y++) {
			for (int x = 0; x < img_width; x++) {
				pixelMatrix[counter] = GetPixel(hdc, x + STARTX, y + STARTY);
				counter++;
				//CHAR szBuffer[255];
				//sprintf_s(szBuffer, "size: %d, %d, %d", x, y, (x - STARTX + 1) * (y - STARTY + 1));
				//MessageBox(hWnd, szBuffer, "File", MB_OK);

			}
		}
	}
	
}

void Viewer::outputScreenRGB(HDC hdc)
{
	int counter = 0;
	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			SetPixel(hdc, x + STARTX - scrollX, y + STARTY - scrollY, pixelMatrix[counter]);
			counter++;
		}
	}
}

void Viewer::zoomHDC()
{
	zoom += 0.2f;
	resetScreen();
}

void Viewer::unzoomHDC()
{
	zoom = zoom <= 1 ? 1 : zoom - 0.2f;
	resetScreen();
}

void Viewer::setScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	scrollX = scrollbar.OnHorizontalScroll(hWnd, wParam, lParam);
	resetScreen();
}

void Viewer::setScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	scrollY = scrollbar.OnVerticalScroll(hWnd, wParam, lParam);
	resetScreen();
}


void Viewer::OnLMBDown(HWND hWnd)
{
	if (isMoveTool) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x1 = x2 = pt.x;
		y1 = y2 = pt.y;
		isPressed = true;
	}
}

void Viewer::OnLMBUp(HWND hWnd)
{
	if (isMoveTool) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
		isPressed = false;

		int difX = x2 - x1;
		if (difX != 0) scrollX += (int)difX / img_width;
		if (scrollX < 0) scrollX = 0;

		int difY = y2 - y1;
		if (difY != 0) scrollY += (int)difY / img_height;
		if (scrollY < 0) scrollY = 0;

		InvalidateRect(hWnd, NULL, TRUE);
	}
}

void Viewer::OnMouseMove(HWND hWnd)
{
	if (isPressed && isMoveTool)
	{
		POINT pt;
		HDC hdc = GetDC(hWnd);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
	}
}

void Viewer::moveTool(int is)
{
	isMoveTool = is;
}