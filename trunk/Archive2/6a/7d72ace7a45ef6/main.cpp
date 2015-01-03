// SampleGDIHackery.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SampleGDIHackery.h"

#include <windows.h>
#include <vector>
#include <exception>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class DeviceContext
{
public:
    enum DeviceCtxState {
		DC_INVALID = -1,
		DC_ACQUIRED,
		DC_CREATED
	};

	enum DeviceCtxActuireFlags {
		DC_CTX_ACQUIRE_CLIENT,
		DC_CTX_ACQUIRE
	};

	DeviceContext()
	{
	}

	DeviceContext(HDC& hDC, enum DeviceCtxState State)
		: m_hDC(hDC)
		, m_State(State)
	{
	}

	BOOL Create(LPCTSTR lpszDevice, LPCTSTR lpszOutput)
	{
		if (!IsAcquired())
		{
			m_hDC = ::CreateDC(NULL, lpszDevice, lpszOutput, NULL);
			return TRUE;
		}

		return FALSE;
	}

	BOOL Attach(HWND hwnd, DeviceCtxActuireFlags flags = DC_CTX_ACQUIRE_CLIENT)
	{
		switch (m_State)
		{
			case DC_INVALID: {
				switch (flags)
				{
				case DC_CTX_ACQUIRE_CLIENT: {
					m_hDC = BeginPaint(hwnd, &m_PS);
				} return TRUE;

				case DC_CTX_ACQUIRE: {
					m_hDC = GetWindowDC(hwnd);
				} return TRUE;

				default: { return FALSE;
				} break;
			}
			
			default: { return FALSE; }
			}
		}
	}

	BOOL Release()
	{
		switch (m_State) {
		case DC_INVALID:
			break;

		case DC_CREATED:
			return ::DeleteDC(m_hDC);

		case DC_ACQUIRED:
			break;
		}

		return FALSE;
	}

	BOOL Release(HWND hWnd)
	{
		switch (m_State) {
		case DC_INVALID:
			break;

		case DC_CREATED:
			return ::DeleteDC(m_hDC);

		case DC_ACQUIRED:
			return ::ReleaseDC(hWnd, m_hDC);
		}

		return FALSE;
	}

	operator HDC() { return m_hDC; }
	bool IsAcquired() { return ( m_hDC != NULL ); }
	
	~DeviceContext()
	{
		
	}
private:
	HDC m_hDC;

	DeviceCtxState m_State;
	PAINTSTRUCT m_PS;
};

class HathorWindow {
	HWND		m_hWnd;
	HBRUSH		m_gzosBkgndBrush;

	DeviceContext	m_hDCNonClientArea;
	DeviceContext	m_hDCWinClientArea;

	typedef LRESULT(*PaintCallbackHandler)(HathorWindow&);

	PaintCallbackHandler NcPaintHandler,
						 WinPaintHandler,
						 DrawWindow;

public:
	HathorWindow(PaintCallbackHandler OnNonClientPaint)
		:/* m_hDCNonClientArea(
		 CreateCompatibleDC(GetWindowDC(hWnd))
		 )
		 ,*/ m_gzosBkgndBrush(CreateSolidBrush(RGB(200, 200, 200)))
		, NcPaintHandler(OnNonClientPaint)
		, WinPaintHandler(NULL)
	{
	}

	HathorWindow(PaintCallbackHandler OnNonClientPaint, PaintCallbackHandler OnWindowPaint)
		:/* m_hDCNonClientArea(
		 CreateCompatibleDC(GetWindowDC(hWnd))
		 )
		 ,*/ m_gzosBkgndBrush(CreateSolidBrush(RGB(200, 200, 200)))
		, NcPaintHandler(OnNonClientPaint)
		, WinPaintHandler(OnWindowPaint)
	{
	}

	HathorWindow(PaintCallbackHandler OnNonClientPaint, PaintCallbackHandler OnWinClientPaint, PaintCallbackHandler OnWindowPaint)
		:/* m_hDCNonClientArea(
		 CreateCompatibleDC(GetWindowDC(hWnd))
		 )
		 ,*/ m_gzosBkgndBrush(CreateSolidBrush(RGB(200, 200, 200)))
		, NcPaintHandler(OnNonClientPaint)
		, WinPaintHandler(OnWindowPaint)
		, DrawWindow(OnWindowPaint)
	{
	}

	~HathorWindow()
	{
		ReleaseDC(m_hWnd, m_hDCNonClientArea);

//		-- Nothing to do here (yet.)
//		ReleaseDC(m_hDCWinClientArea);
	}

	RECT GetRect()
	{
		RECT r;
		::GetWindowRect(m_hWnd, &r);

		return r;
	}

	BOOL PaintWindow(HWND hwnd)
	{
		m_hDCNonClientArea.Attach(hwnd, DeviceContext::DC_CTX_ACQUIRE);
		m_hDCWinClientArea.Attach(hwnd);

		m_hWnd = hwnd;
		NcPaintHandler(*this);

		if (WinPaintHandler != NULL)
			WinPaintHandler(*this);

		DrawWindow(*this);
		m_hDCNonClientArea.Release();
		
		m_hDCWinClientArea.Release();
		m_hWnd = NULL;

		return TRUE;
	}

	int top() { return GetRect().top; }
	int right() { return GetRect().right; }
	int bottom() { return GetRect().bottom; }
	int left() { return GetRect().left; }

	HDC GetDC() { return ::GetWindowDC(m_hWnd); }
	BOOL ReleaseTempDC()
	{
		return (
			::DeleteDC(m_hDCNonClientArea) &&
			::DeleteDC(m_hDCWinClientArea)
		);
	}

	HDC NonClientArea() { return m_hDCNonClientArea; }
	HDC WinClientArea() { return m_hDCWinClientArea; }
};


LRESULT DrawNonClientArea(HathorWindow&);
LRESULT PaintWindow(HathorWindow&);

HathorWindow Window(DrawNonClientArea, PaintWindow);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow)
{
	MSG  msg;
	WNDCLASSW wc = {0};

	wc.lpszClassName	= L"hathor.0";
	wc.hInstance		= hInstance;
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground	= GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc		= WndProc;
	wc.hCursor			= LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName, _T("Hathor Window"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, (100 * 2) + 40, 220, 240, NULL, NULL, hInstance, NULL);
	
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

  return (int) msg.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam)
{
	try
	{
		switch(msg)
		{
		case WM_ERASEBKGND:
			break;
		
		case WM_CREATE:
			break;

		case WM_NCPAINT: {
			Window.PaintWindow(hwnd);
			
		} break;

		case WM_DESTROY:

			PostQuitMessage(0);
			break;
		
		default:
			std::string message;
			message += "Window message not supported.";
			
			throw std::exception();
		}

		return TRUE;
	}
	catch (std::exception& ex)
	{
//		MessageBoxA(hwnd, ex.what(), "Hathor UI", MB_OK);
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
}

LRESULT PaintWindow(HathorWindow& window)
/*
	hDCNonClient		@HDC
	Non-client memory buffer for the window to render to.

	hDCWindArea			@HDC
	win32 Device Context to use when drawing the client area.
*/
{
	BitBlt(window.GetDC(), 
		0, 0, 0, 0, window.NonClientArea(),
		window.GetRect().right, window.GetRect().bottom,
		SRCCOPY);

	window.ReleaseTempDC();
	return TRUE;
}

LRESULT DrawNonClientArea(HathorWindow& window)
{
  HPEN hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
  HPEN holdPen = (HPEN)SelectObject(window.NonClientArea(), hPen);

  HBRUSH hBrush1 = CreateSolidBrush(RGB(200, 200, 200));
  HBRUSH hBrush2 = CreateSolidBrush(RGB(240, 63, 19));
  HBRUSH hBrush3 = CreateSolidBrush(RGB(240, 210, 18));
  HBRUSH hBrush4 = CreateSolidBrush(RGB(9, 189, 21));

  Rectangle(window.NonClientArea(), 0, 0, window.right(), window.bottom());
  HBRUSH holdBrush = (HBRUSH)SelectObject(window.NonClientArea(), hBrush1);

  int left = 0, top = 0, bottom = 30, right = window.right();
  
  Rectangle(window.NonClientArea(), left, top, right, bottom + 58);
  SelectObject(window.NonClientArea(), hBrush2);
  
  left = 30, top = 30, bottom += 60, right = 200;
  top += 70; bottom += 70;

  /*
  Rectangle(hdc, left, top, right, bottom + 58);
  SelectObject(hdc, hBrush3);
  
  left += (30 * 5) + 30; top -= 70;
  right += left - 30; bottom -= 12;

  Rectangle(hdc, left, top, right, bottom);
  SelectObject(hdc, hBrush4);
  
  top += 70; bottom += (top - 30);
  
  Rectangle(hdc, left, top, right, bottom);
  */

  SelectObject(window.NonClientArea(), holdPen);
  SelectObject(window.NonClientArea(), holdBrush);
  
  DeleteObject(hPen);
  DeleteObject(hBrush1);
  DeleteObject(hBrush2);
  DeleteObject(hBrush3);
  DeleteObject(hBrush4);

  return TRUE;
}