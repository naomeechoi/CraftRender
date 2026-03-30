#include "SpecularMappingShader.h"
#include "Texture/Texture.h"
#include "Resource/TextureLoader.h"

namespace Craft
{
	SpecularMappingShader::SpecularMappingShader(
		const std::string& diffuseTextureName,
		const std::string& specularTextureName)
		: Shader(L"SpecularMapping")
	{
		TextureLoader::Get().Load(diffuseTextureName, diffuseTexture);
		TextureLoader::Get().Load(specularTextureName, specularTexture);
	}

	void Craft::SpecularMappingShader::Bind()
	{
		Shader::Bind();
		if (diffuseTexture.lock())
			diffuseTexture.lock()->Bind(0);

		if (specularTexture.lock())
			specularTexture.lock()->Bind(1);
	}
}
