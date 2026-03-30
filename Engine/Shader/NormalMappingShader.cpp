#include "NormalMappingShader.h"
#include "Texture/Texture.h"
#include "Resource/TextureLoader.h"

namespace Craft
{
	NormalMappingShader::NormalMappingShader(
		const std::string& diffuseTextureName,
		const std::string& specularTextureName,
		const std::string& normalTextureName)
		: Shader(L"NormalMapping")
	{
		TextureLoader::Get().Load(diffuseTextureName, diffuseTexture);
		TextureLoader::Get().Load(specularTextureName, specularTexture);
		TextureLoader::Get().Load(normalTextureName, normalTexture);
	}

	void Craft::NormalMappingShader::Bind()
	{
		Shader::Bind();
		if (diffuseTexture.lock())
			diffuseTexture.lock()->Bind(0);

		if (specularTexture.lock())
			specularTexture.lock()->Bind(1);

		if (normalTexture.lock())
			normalTexture.lock()->Bind(2);
	}
}
