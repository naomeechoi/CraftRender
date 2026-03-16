#pragma once
#include "Core/Common.h"

namespace Craft
{
	class CRAFT_API Vector3
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		~Vector3() = default;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(const Vector3& other) const;
		Vector3 operator*(const float scale) const;

		// 내적(Dot Product/Inner Product)
		friend CRAFT_API float Dot(const Vector3& left, const Vector3& right);

		// 외적(Cross Product/Outer Product)
		friend CRAFT_API Vector3 Cross(const Vector3& left, const Vector3& right);

		float Length() const;

		Vector3 Normalized() const;

		static Vector3 Zero;
		static Vector3 One;
		static Vector3 Right;
		static Vector3 Up;
		static Vector3 Forward;
	};
}
