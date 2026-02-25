#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <string>

namespace Craft
{
	class Win32Window;

	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Initialize(uint32_t width, uint32_t height, const Win32Window& window);
	private:
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr;

		D3D11_VIEWPORT viewport = {};

		uint32_t width = 0;
		uint32_t height = 0;
	};
}