#pragma once

#include "Shader.h"
#include <memory>
#include <string>

namespace Craft
{
	class Texture;

	class CRAFT_API NormalMappingShader : public Shader
	{
	public:
		NormalMappingShader(const std::string& diffuseTextureName, const std::string& specularTextureName, const std::string& normalTextureName);
		virtual void Bind() override;

	private:
		std::weak_ptr<Texture> diffuseTexture;
		std::weak_ptr<Texture> specularTexture;
		std::weak_ptr<Texture> normalTexture;
	};
}

