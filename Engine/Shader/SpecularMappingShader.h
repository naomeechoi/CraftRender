#pragma once

#include "Shader.h"
#include <memory>
#include <string>

namespace Craft
{
	class Texture;

	class CRAFT_API SpecularMappingShader : public Shader
	{
	public:
		SpecularMappingShader(const std::string& diffuseTextureName, const std::string& specularTextureName);
		virtual void Bind() override;

	private:
		std::weak_ptr<Texture> diffuseTexture;
		std::weak_ptr<Texture> specularTexture;
	};
}

