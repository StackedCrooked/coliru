#include "stdafx.h"
#include <windows.h>
#include <gdiplus.h>


HDC hdc = GetDC(NULL); // get the desktop device context
HDC hDest = CreateCompatibleDC(hdc); // create a device context to use yourself

// get the height and width of the screen
int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);

HBITMAP hbDesktop = CreateCompatibleBitmap( hdc, width, height);

SelectObject(hDest, hbDesktop);                //Here

BitBlt(hDest, 0,0, width, height, hdc, 0, 0, SRCCOPY);   //Here

ReleaseDC(NULL, hdc);   //Here

DeleteDC(hDest);    //...and Here