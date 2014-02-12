#define BIND_MSG(msg) case (msg): Wnd_Main_##msg (hWnd, wParam, lParam); break;

#define WM_PAINT 0x000F

int main() {
    switch (0) {
        BIND_MSG(WM_PAINT)
        // -> case WM_PAINT: Wnd_Main_WM_PAINT (hWnd, wParam, lParam); break;
    }
}

