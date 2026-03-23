#pragma once
#include "Core/Common.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include <stdint.h>

namespace Craft
{
	class CRAFT_API Vertex
	{
	public:
		Vector3 position;
		Vector2 texCoord;
		Vector3 normal;

		Vertex(const Vector3& position,
			const Vector2& texCoord = Vector2::Zero,
			const Vector3& normal = Vector3::Zero);
		~Vertex() = default;

		static uint32_t Stride() { return sizeof(Vertex); };
	
	};
}

