#include "Core/Win32Window.h"
#include "Graphics/GraphicsContext.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main()
{
    // Register the window class.
    uint32_t width = 1280;
    uint32_t height = 800;
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    Craft::Win32Window window(width, height, L"Craft Engine", hInstance, WindowProc);
    if (!window.Initialize())
        return -1;
   
    Craft::GraphicsContext context;
    context.Initialize(width, height, window);
    // Run the message loop.
    MSG msg = { };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {

        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}