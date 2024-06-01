//
// Created by manish on 01-06-2024.
//

#include "silverocto-lib.h"
// #############################################################################
//                           Platform Globals
// #############################################################################
static bool running = true;

// #############################################################################
//                           Platform Functions
// #############################################################################
bool platform_create_window(int width, int height, const char *title);
void platform_update_window();

// #############################################################################
//                           Windows Platform
// #############################################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// #############################################################################
//                           Windows Globals
// #############################################################################
static HWND window;

// #############################################################################
//                           Platform Implementations
// #############################################################################

LRESULT CALLBACK windows_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    switch (msg) {
        case WM_CLOSE: {
            running = false;
            break;
        }
        default: {
            result = DefWindowProcA(window, msg, wParam, lParam);
        }
    }
    return  result;
}

bool platform_create_window(int width, int height, const char *title)
{
    HINSTANCE instance = GetModuleHandleA(nullptr);

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // This means we decide the look of the cursor(arrow)
    wc.lpszClassName = title;                 // This is NOT the title, just a unique identifier(ID)
    wc.lpfnWndProc = windows_window_callback; // Callback for Input into the Window

    if (!RegisterClassA(&wc))
    {
        return false;
    }

    int dwStyle = WS_OVERLAPPEDWINDOW;

    window = CreateWindowExA(0,
        title,
        title,
        dwStyle,
        100,
        100,
        width,
        height,
        nullptr, // parent
        nullptr, // menu
        instance,
        nullptr); // lpParam

    if (window == nullptr)
    {
        return false;
    }

    ShowWindow(window, SW_SHOW);
    return true;
}

void platform_update_window() {
    MSG msg;
    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}


#endif

int main()
{
    platform_create_window(1200, 720, "Silver Octo");
    while (running)
    {
        platform_update_window();
    }
    SM_TRACE("Stopped");
    return 0;
}
