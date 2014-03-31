#include "HTMLTransientWindow.h"
#include "Utils/Strings.h"
#include "Utils/Windows/Support.h"
#include "Poco/Exception.h"
#include <map>
#include <windows.h>
#include <atlbase.h>
#include <comutil.h>
#include <strsafe.h>


#ifdef _DEBUGFREE // detect the access to freed memory
#undef free
#define free(p) _free_dbg(p, _NORMAL_BLOCK); *(int*)&p = 0x666;
#endif

extern CComModule _Module;

namespace abc
{
    static bool sHTMLTransientWindowRegistered = false;

	typedef std::map<HWND, HTMLTransientWindow*> HTMLTransientWindowInstances;
	static HTMLTransientWindowInstances sHTMLTransientWindowInstances;

	
	HTMLTransientWindow::HTMLTransientWindow(HMODULE inModuleHandle, HWND inParentWindow, int inWidth, int inHeight) :
		mModuleHandle(inModuleHandle),
		mParentWindow(inParentWindow),
		mWindowHandle(0)
	{	
		// TODO: move this code to a better place
		if (!sHTMLTransientWindowRegistered)
		{
			BOOL result = AtlAxWinInit();
			_pAtlModule = &_Module;
			assert(result);
			sHTMLTransientWindowRegistered = true;
		}

		RECT rw;
		::GetWindowRect(inParentWindow, &rw);
		int w = inWidth;
		int h = inHeight;
		int x = rw.left + ((rw.right - rw.left) - w)/2;
		int y = rw.bottom;

		DWORD dwStyle = WS_POPUP | WS_BORDER | WS_VSCROLL;
		DWORD dwExStyle = WS_EX_TOOLWINDOW |      /* So it doesn't show up in taskbar */
						  WS_EX_DLGMODALFRAME |   /* Get the edges right */
						  WS_EX_WINDOWEDGE |
						  WS_EX_TOPMOST; 			/* So it isn't obscured */

		mWindowHandle = ::CreateWindowExA
		(
			dwExStyle,
			ATLAXWIN_CLASS,
			"about:blank",
			dwStyle,
			x, y, w, h,
			inParentWindow,
			NULL,
			mModuleHandle, NULL
		);

		// Subclass the window
		mOrigProc = (WNDPROC)(LONG_PTR)SetWindowLongPtr(mWindowHandle, GWLP_WNDPROC, (LONG)(LONG_PTR)HTMLTransientWindow::Proc);

		// Create the HWND object mapping
		HTMLTransientWindowInstances::iterator it = sHTMLTransientWindowInstances.find(mWindowHandle), end = sHTMLTransientWindowInstances.end();
		assert(it == end);
		if (it == end)
		{
			sHTMLTransientWindowInstances.insert(std::make_pair(mWindowHandle, this));
		}
	}


	HTMLTransientWindow::~HTMLTransientWindow()
	{	
		(WNDPROC)(LONG_PTR)SetWindowLongPtr(mWindowHandle, GWLP_WNDPROC, (LONG)(LONG_PTR)mOrigProc);


		HTMLTransientWindowInstances::iterator it = sHTMLTransientWindowInstances.find(mWindowHandle), end = sHTMLTransientWindowInstances.end();
		assert(it != end);
		if (it != end)
		{
			sHTMLTransientWindowInstances.erase(it);
		}		

		DestroyWindow(mWindowHandle);
	}
	
	
	void HTMLTransientWindow::OnBeforeNavigate2(IWebBrowser2 *window, const CString &url, bool *cancel)
	{
		if (mClickAction)
		{
			*cancel = true;			
			const TCHAR * buffer = url.GetString();
			mClickAction(abc::StringToUTF8(buffer));
			PostQuitMessage(0);
		}
	}
		

	void HTMLTransientWindow::OnDocumentComplete(IWebBrowser2 *window, const CString &url)
	{
	}


	void HTMLTransientWindow::showWithUrl(const std::string & inUrl)
	{
		// Get the IWebBrowser2 control
		CAxWindow2 helperWindow;
		helperWindow.Attach(mWindowHandle);
		HRESULT hr = helperWindow.QueryControl(&mWebBrowser);

		Init(mWebBrowser);

		abc::String uni16String = UTF8ToString(inUrl);
		CComBSTR bstr = uni16String.c_str();
		mWebBrowser->Navigate(bstr, 0, 0, 0, 0);

		startMessageLoop();

		Teardown();
		
		helperWindow.Detach();
	}


	void HTMLTransientWindow::executeJavascript(const std::string & inCode)
	{
		if (!mWebBrowser)
		{
			throw Poco::Exception("IWebBrowser2 not instantiated");
		}

		HRESULT hr = E_FAIL;
		CComPtr<IDispatch> disp;
		if (FAILED( hr = mWebBrowser->get_Document(&disp)) || !disp)
		{
			throw Poco::Exception("IWebBrowser2::get_Document failed", hr);
		}

		CComPtr<IHTMLDocument2> document;
		if (FAILED(hr = disp->QueryInterface(IID_IHTMLDocument2,(void**)&document)) || !document)
		{
			throw Poco::Exception("IDispatch::QueryInterface for IID_IHTMLDocument2 failed", hr);
		}
		
		CComPtr<IHTMLWindow2> window;
		if (FAILED(hr = document->get_parentWindow(&window)) || !window)
		{
			throw Poco::Exception("IHTMLDocument2::get_parentWindow failed", hr);
		}
		abc::String codeString = abc::UTF8ToString(inCode);
		CComBSTR code = codeString.c_str();
		CComBSTR language = TEXT("javascript");	
		VARIANT returnValue = {0};

		if (FAILED(hr = window->execScript(code, language, &returnValue)))
		{
			throw Poco::Exception("IHTMLWindow2::execScript failed", hr);
		}
	}


	HRESULT HTMLTransientWindow::LoadWebBrowserFromStream(IWebBrowser* pWebBrowser, IStream* pStream)
	{
		HRESULT hr;
		IDispatch* pHtmlDoc = NULL;
		IPersistStreamInit* pPersistStreamInit = NULL;

		// Retrieve the document object.
		hr = pWebBrowser->get_Document( &pHtmlDoc );
		if ( SUCCEEDED(hr) )
		{
			// Query for IPersistStreamInit.
			hr = pHtmlDoc->QueryInterface( IID_IPersistStreamInit,  (void**)&pPersistStreamInit );
			if ( SUCCEEDED(hr) )
			{
				// Initialize the document.
				hr = pPersistStreamInit->InitNew();
				if ( SUCCEEDED(hr) )
				{
					// Load the contents of the stream.
					hr = pPersistStreamInit->Load( pStream );
				}
				pPersistStreamInit->Release();
			}
		}
		return hr;
	}


	void HTMLTransientWindow::showWithHTML(const std::string & inHTML, ClickAction inClickAction)
	{
		mClickAction = inClickAction;
		// Get the IWebBrowser2 control
		CAxWindow2 helperWindow;
		helperWindow.Attach(mWindowHandle);
		HRESULT hr = helperWindow.QueryControl(&mWebBrowser);

		Init(mWebBrowser);

		HGLOBAL hHTMLText = GlobalAlloc(GMEM_MOVEABLE, sizeof(char)*(inHTML.size()));
		if (hHTMLText)
		{
			void * pHTMLBuffer = ::GlobalLock(hHTMLText);
			if (pHTMLBuffer)
			{
				::CopyMemory(pHTMLBuffer, inHTML.data(), sizeof(char)*(inHTML.size()));
				IStream * pStream;
				if (::CreateStreamOnHGlobal(hHTMLText, FALSE, &pStream) == S_OK)
				{
					LoadWebBrowserFromStream(mWebBrowser, pStream);
					pStream->Release();
				}
				::GlobalUnlock(hHTMLText);
			}
			::GlobalFree(hHTMLText);
		}

		startMessageLoop();

		Teardown();
		
		helperWindow.Detach();
	}


	void HTMLTransientWindow::startMessageLoop()
	{	

		::ShowWindow(mWindowHandle, SW_SHOW);
		MSG message;
		while (GetMessage(&message, NULL, 0, 0))
		{
			if (message.message >= WM_KEYFIRST && message.message <= WM_KEYLAST && ::IsChild(mWindowHandle, message.hwnd))
			{
				CComPtr<IOleInPlaceActiveObject> active_object;
				mWebBrowser->QueryInterface(&active_object);

				// Enables access keys in side the browser control.
				if (active_object != NULL)
				{
					active_object->TranslateAccelerator(&message);
				}

				// Prevent the dialog box from handling certain messages.
				// - tab: If the dialog handles this, if shifts focus away from the
				//   browser control each time tab is pressed.
				// - syschar: This is ALT+<anything except F4>. We prevent the dialog
				//   from handling these because otherwise it beeps because there is no
				//   menu bar visible.
				if (message.wParam == VK_TAB || message.message == WM_SYSCHAR)
				{
					ZeroMemory(&message, sizeof(MSG));
				}

				// Pressing the escape button closes the popup
				if (message.wParam == VK_ESCAPE)
				{
					break;
				}
			}


			HWND hActive = GetActiveWindow();
			if (! IsDialogMessage(hActive, &message))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
	}


	LRESULT CALLBACK HTMLTransientWindow::Proc(HWND hWnd, UINT inMessage, WPARAM wParam, LPARAM lParam)
	{
		HTMLTransientWindowInstances::iterator it = sHTMLTransientWindowInstances.find(hWnd), end = sHTMLTransientWindowInstances.end();

		if (it == end)
		{
			return DefWindowProc(hWnd, inMessage, wParam, lParam);
		}
		HTMLTransientWindow * pThis = it->second;

		switch(inMessage)
		{
			case WM_ACTIVATE:
			{
				if (LOWORD(wParam) == WA_INACTIVE)
				{
					// Get the class name for the activated window
					TCHAR className[512];
					::GetClassName((HWND)lParam, className, 512);
					abc::String classNameString(className);

					// If the activated window is not of type "Auto-Suggest Dropdown"
					// then we assume that the user clicked out of the window, so 
					// we destroy the popup.
					if (classNameString != TEXT("Auto-Suggest Dropdown"))
					{
						PostQuitMessage(0);
					}
				}
				break;
			}
			case WM_CLOSE:
			{
				LRESULT res = CallWindowProc(pThis->mOrigProc, hWnd, inMessage, wParam, lParam);
				delete pThis;
				return res;
			}
			default:
			{
				break;
			}
		};

		return CallWindowProc(pThis->mOrigProc, hWnd, inMessage, wParam, lParam);
	}

} // namespace abc
