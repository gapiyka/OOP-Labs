#include "viewer.h"


Viewer::Viewer() {
	hWnd = NULL;
	hInst = NULL;
	IsOpenedFile = 0;
	zoom = 1;
	scrollX = 0;
	scrollY = 0;
	isMoveTool = 0;
	isPressed = false;
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

vector<COLORREF> Viewer::saveFile(int* img_w, int* img_h) {
	*img_w = img_width;
	*img_h = img_height;
	return pixelMatrix;
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


void Viewer::brightnessChange()
{
	int counter = 0;
	int R, G, B, brightnessMultiplier;
	Func_MOD1(hInst, hWnd, &brightnessMultiplier);

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			COLORREF color = pixelMatrix[counter];

			R = GetRValue(color) + brightnessMultiplier;
			G = GetGValue(color) + brightnessMultiplier;
			B = GetBValue(color) + brightnessMultiplier;

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter] = RGB(R, G, B);
			counter++;
		}
	}

	resetScreen();
}

void Viewer::contrastChange()
{
	int counter = 0;
	int R, G, B, contrast;
	const int half = 127;
	Func_MOD2(hInst, hWnd, &contrast);
	float factor = (259.0 * (contrast + 255.0)) / (255.0 * (259.0 - contrast));
	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			COLORREF color = pixelMatrix[counter];

			R = (factor * (GetRValue(color) - 128) + 128);
			G = (factor * (GetGValue(color) - 128) + 128);
			B = (factor * (GetBValue(color) - 128) + 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter] = RGB(R, G, B);
			counter++;
		}
	}
	resetScreen();
}

void Viewer::rgbChange()
{
	int counter = 0;
	int R, G, B, rMultiplier, gMultiplier, bMultiplier;
	Func_MOD3(hInst, hWnd, &rMultiplier, &gMultiplier, &bMultiplier);

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			COLORREF color = pixelMatrix[counter];

			R = GetRValue(color) + rMultiplier;
			G = GetGValue(color) + gMultiplier;
			B = GetBValue(color) + bMultiplier;

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter] = RGB(R, G, B);
			counter++;
		}
	}

	resetScreen();
}