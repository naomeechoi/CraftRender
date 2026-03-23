#pragma once
#include "Core/Common.h"
#include <string>
#include <memory>
#include <d3d11.h>

namespace Craft
{
	struct TextureData
	{
		TextureData() = default;
		~TextureData()
		{
			free(pixelArray);
			pixelArray = nullptr;
		}

		int width = 0;
		int height = 0;
		int channelCount = 0;
		void* pixelArray = nullptr;
	};

	class CRAFT_API Texture
	{
		enum class BindType
		{
			VertexShader,
			PixelShader,
		};

	public:
		Texture(const std::string& name, BindType bindType = BindType::PixelShader);
		virtual ~Texture();

		//생성과 바인딩은 누가 담당하나? 정리해놓기
		void Bind(uint32_t index = 0);

	private:
		void ConvertToRGBA(std::unique_ptr<TextureData>& textureData);

	private:
		std::string name;
		BindType bindType = BindType::PixelShader;
		std::unique_ptr<TextureData> data;
		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		ID3D11SamplerState* samplerState = nullptr;
	};
}

