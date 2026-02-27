#include "GraphicsContext.h"
#include "Core/Win32Window.h"
#include "Core/Common.h"
#include <cassert>

namespace Craft
{
	GraphicsContext* GraphicsContext::instance = nullptr;
	GraphicsContext::GraphicsContext()
	{
		assert(!instance);
		instance = this;
	}

	GraphicsContext::~GraphicsContext()
	{
		SafeRelease(device);
		SafeRelease(context);
		SafeRelease(swapChain);
	}

	void GraphicsContext::Initialize(const Win32Window& window)
	{
		width = window.Width();
		height = window.Height();

		CreateDevice();
		CreateSwapChain(window);
		CreateViewport(window);
		CreateRenderTargetView();
		context->RSSetViewports(1, &viewport);
	}

	void GraphicsContext::BeginScene(float red, float green, float blue)
	{
		// 그려지는 정보를 받는게 렌더타겟뷰, 최종적으로 그려지는 목적지가 백버퍼
		// 빈 도화지 준비 -> 그리기 -> 모니터로 전달
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		// 백버퍼랑은 무슨관계지?
		float backgroundColor[4] = { red, green, blue, 1.0f };
		context->ClearRenderTargetView(renderTargetView, backgroundColor);
	}

	void GraphicsContext::EndScene(uint32_t vsync)
	{
		swapChain->Present(0, 0);
	}

	GraphicsContext& GraphicsContext::Get()
	{
		assert(instance);
		return *instance;
	}

	void GraphicsContext::CreateDevice()
	{

		uint32_t flag = 0;
#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featrueLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		HRESULT result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, flag, featrueLevels, _countof(featrueLevels),
			D3D11_SDK_VERSION, &device, nullptr, &context);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}
	}

	void GraphicsContext::CreateSwapChain(const Win32Window& window)
	{
		IDXGIFactory* factory = nullptr;
		HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));

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

		SafeRelease(factory);
	}

	void GraphicsContext::CreateViewport(const Win32Window& window)
	{
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window.Width());
		viewport.Height = static_cast<float>(window.Height());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
	}

	void GraphicsContext::CreateRenderTargetView()
	{
		ID3D11Texture2D* backbuffer = nullptr;
		HRESULT result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		result = device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);

		if (FAILED(result))
		{
			SafeRelease(backbuffer);
			__debugbreak();
			return;
		}

		SafeRelease(backbuffer);
	}

}