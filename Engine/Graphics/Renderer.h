#pragma once
#include <vector>
#include <d3d11.h>

namespace Craft
{
	struct RenderCommand
	{
		// 정점 버퍼(메모리 덩어리)
		ID3D11Buffer* vertexBuffer = nullptr;

		// 인덱스 버퍼
		ID3D11Buffer* indexBuffer = nullptr;

		// 정점의 생김새
		ID3D11InputLayout* inputLayout = nullptr;

		// 필수 쉐이더
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;

		uint32_t indexCount = 0;
	};

	// DrawCall 담당
	// RHI - Render Hardware Interface
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Initialize();
		void DrawScene();

	private:
		std::vector<RenderCommand> renderQueue;
	};
}

