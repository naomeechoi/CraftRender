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

		Vertex(const Vector3& position, Vector2 texCoord = Vector2::Zero);
		~Vertex() = default;

		static uint32_t Stride() { return sizeof(Vertex); };
	
	};
}

