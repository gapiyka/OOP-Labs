#pragma once
#include "scrollbar.h"

void Scrollbar::OnNewBmp(HWND hWnd, int width, int height) {
    nWidth = width;
    nHeight = height;
    SetScrollRange(hWnd, SB_VERT, nMinPos, nHeight, TRUE);
    SetScrollRange(hWnd, SB_HORZ, nMinPos, nWidth, TRUE);
}

int Scrollbar::OnVerticalScroll(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    int divine = (int)nHeight / 10;
    switch (LOWORD(wParam))
        {
        case SB_LINEUP:
            posY -= divine;
            break;
        case SB_LINEDOWN:
            posY += divine;
            break;
        case SB_TOP:
            posY -= divine;
            break;
        case SB_BOTTOM:
            posY += divine;
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            posY = HIWORD(wParam);
            break;
        default: break;
        }
    if (posY <= 1) posY = 0;
    if (posY > nHeight) posY = nHeight;
    SetScrollPos(hWnd, SB_VERT, posY, TRUE);

    return posY;
}


int Scrollbar::OnHorizontalScroll(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    int divine = (int)nWidth/10;
    switch (LOWORD(wParam))
    {
    case SB_LINELEFT:
        posX -= divine;
        break;
    case SB_LINEDOWN:
        posX += divine;
        break;
    case SB_TOP:
        posX -= divine;
        break;
    case SB_BOTTOM:
        posX += divine;
        break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        posX = HIWORD(wParam);
        break;
    default: break;
    }
    if (posX <= 1) posX = 0;
    if (posX > nWidth) posX = nWidth;
    SetScrollPos(hWnd, SB_HORZ, posX, TRUE);

    return posX;
}