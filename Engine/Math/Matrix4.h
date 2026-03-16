#pragma once
#include "Core/Common.h"
#include "Vector3.h"

namespace Craft
{
	class CRAFT_API Matrix4
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& other);
		~Matrix4() = default;

		// 전치
		static Matrix4 Transpose(const Matrix4& matrix);

		// 역행렬
		static Matrix4 Inverse(const Matrix4& matrix);

		// 아핀 변환(affine transformation), 동차좌표계

		static Matrix4 Translation(float x, float y, float z);
		static Matrix4 Translation(const Vector3& position);

		static Matrix4 Rotation(float x, float y, float z);
		static Matrix4 Rotation(const Vector3& rotation);
		static Matrix4 RotationX(float angle);
		static Matrix4 RotationY(float angle);
		static Matrix4 RotationZ(float angle);

		static Matrix4 Scale(float x, float y, float z);
		static Matrix4 Scale(const Vector3& scale);
		static Matrix4 Scale(float scale);

		static Matrix4 LookAt(const Vector3& position, const Vector3& target, const Vector3& up);

		Matrix4& operator=(const Matrix4& other);
		Matrix4 operator*(const Matrix4& other) const;
		Matrix4& operator*=(const Matrix4& other);

		friend CRAFT_API Vector3 operator*(const Matrix4& m, const Vector3& v);
		friend CRAFT_API Vector3 operator*(const Vector3& v, const Matrix4& m);

		static Matrix4 Identity;
		static constexpr float degreeToRadian = 3.141592f / 180.0f;
		static constexpr float radianToDegree = 180.0f / 3.141592f;
	private:
		union
		{
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			float elements[4 * 4] = {};
		};
	};
}

