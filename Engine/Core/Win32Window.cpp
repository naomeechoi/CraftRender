#include "Win32Window.h"

namespace Craft
{
	Win32Window::Win32Window(uint32_t width, uint32_t height, HINSTANCE instance, WNDPROC messageProcedure)
		: width(width), height(height), instance(instance), messageProcedure(messageProcedure)
	{
	}

	Win32Window::~Win32Window()
	{
		UnregisterClass(className, instance);
        delete className;
        className = nullptr;
	}

	bool Win32Window::Initialize()
	{
        WNDCLASS wc = { };
        wc.lpfnWndProc = messageProcedure;
        wc.hInstance = instance;
        wc.lpszClassName = className;

        if (!RegisterClass(&wc))
            return false;

        RECT rect{ 0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
        uint32_t windowWidth = rect.right - rect.left;
        uint32_t windowHeight = rect.bottom - rect.top;

        uint32_t positionX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
        uint32_t positionY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

        // Create the window.
        handle = CreateWindow(
            className,
            title.c_str(),
            WS_OVERLAPPEDWINDOW,
            positionX, positionY, windowWidth, windowHeight,
            nullptr,
            nullptr,
            instance,
            nullptr
        );

        if (!handle)
        {
            return false;
        }

        ShowWindow(handle, SW_SHOW);
        return true;
	}
}