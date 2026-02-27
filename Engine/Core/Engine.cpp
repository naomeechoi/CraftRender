#include "Engine.h"
#include "Win32Window.h"
#include "Graphics/GraphicsContext.h"

namespace Craft
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	bool Engine::Initialize(HINSTANCE hinstance)
	{
		window = std::make_unique<Win32Window>(
			setting.width,
			setting.height,
			setting.title,
			hinstance,
			Win32MessageProcedure);

		if (!window->Initialize())
		{
			__debugbreak();
			return false;
		}

		graphicsContext = std::make_unique<GraphicsContext>();
		graphicsContext->Initialize(*window);

		return true;
	}

	void Engine::Run()
	{
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
				graphicsContext->BeginScene(0.6f, 0.7f, 0.8f);
				graphicsContext->EndScene(setting.vsync);
			}
		}
	}

	LRESULT Engine::Win32MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(handle, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(handle, &ps);
		}
		return 0;

		}

		return DefWindowProc(handle, message, wparam, lparam);
	}
}