#pragma once
#include "framework.h"

class Scrollbar {
	private:
		int posX = 0;
		int posY = 0;
		int nWidth = 0;
		int nHeight = 0;
		const int nMinPos = 0;
	public:
		void OnNewBmp(HWND hWnd, int width, int height);
		int OnVerticalScroll(HWND hWnd, WPARAM wParam, LPARAM lParam);
		int OnHorizontalScroll(HWND hWnd, WPARAM wParam, LPARAM lParam);
};