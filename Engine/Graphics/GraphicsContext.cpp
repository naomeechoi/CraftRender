#include "GraphicsContext.h"
#include "../Core/Win32Window.h"

namespace Craft
{
	GraphicsContext::GraphicsContext()
	{
	}

	GraphicsContext::~GraphicsContext()
	{
		if (device)
		{
			device->Release();
			device = nullptr;
		}

		if (context)
		{
			context->Release();
			context = nullptr;
		}

		if (swapChain)
		{
			swapChain->Release();
			swapChain = nullptr;
		}
	}

	void GraphicsContext::Initialize(uint32_t width, uint32_t height, const Win32Window& window)
	{
		uint32_t flag = 0;
#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featrueLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		HRESULT result = D3D11CreateDevice(nullptr,
											D3D_DRIVER_TYPE_HARDWARE,
											nullptr,
											flag,
											featrueLevels,
											_countof(featrueLevels),
											D3D11_SDK_VERSION,
											&device,
											nullptr,
											&context);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		IDXGIFactory* factory = nullptr;
		result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(& factory));

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = true;
		swapChainDesc.OutputWindow = window.Handle();
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = window.Width();
		swapChainDesc.BufferDesc.Height = window.Height();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		factory->CreateSwapChain(device, &swapChainDesc, &swapChain);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		factory->Release();
		factory = nullptr;

		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window.Width());
		viewport.Height = static_cast<float>(window.Height());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
	}
}