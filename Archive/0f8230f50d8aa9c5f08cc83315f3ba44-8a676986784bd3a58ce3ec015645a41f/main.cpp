#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            auto mybuttonid = (HMENU)(1);

            CreateWindowEx(
                0,
                "BUTTON",
                "mybuttontext",
                BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
                100,100,
                128,32,
                hwnd,
                mybuttonid,
                NULL,
                NULL
            );

            return 0;
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int main() {
    char szClassName[] = "abc";
    auto hInst = GetModuleHandle(nullptr);
    const auto SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
    const auto SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

    WNDCLASSEX wce;
    ZeroMemory(&wce, sizeof wce);
    wce.cbSize = sizeof wce;
    wce.lpfnWndProc = WndProc;
    wce.lpszClassName = szClassName;

    RegisterClassEx(&wce);

    HWND hwnd = CreateWindowEx(
        0,                  /* Extended possibilites for variation */
        szClassName,        /* Classname */
        "KamiPhone",        /* Title Text */
        WS_OVERLAPPEDWINDOW,/* default window */
        CW_USEDEFAULT,      /* Windows decides the position */
        CW_USEDEFAULT,      /* where the window ends up on the screen */
        SCREEN_WIDTH,       /* Width */
        SCREEN_HEIGHT,      /* Height */
        HWND_DESKTOP,       /* The window is a child-window to desktop */
        NULL,               /* No menu */
        hInst,              /* Program Instance handler */
        NULL                /* No Window Creation data */
    );

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
