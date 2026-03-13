#include "Vector3.h"
namespace Craft
{
	Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
	Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);

	Vector3::Vector3(float x, float y, float z)
		:x(x), y(y), z(z)
	{
	}

	Vector3 Craft::Vector3::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 Vector3::operator*(const float scale) const
	{
		return Vector3(x * scale, y * scale, z * scale);
	}

	CRAFT_API float Dot(const Vector3& left, const Vector3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	CRAFT_API Vector3 Cross(const Vector3& left, const Vector3& right)
	{

		return Vector3(left.y*right.z - left.z*right.y,
			left.z * right.x - left.x*right.z,
			left.x *right.y - left.y*right.z);
	}
}