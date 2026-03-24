#include "CameraActor.h"
#include "Math/Transform.h"
#include "Graphics/Renderer.h"
#include "Core/Engine.h"

namespace Craft
{
	CameraActor::CameraActor(
		float fieldOfView,
		float nearDistance,
		float farDistance)
		: fieldOfView(fieldOfView),
		width(static_cast<float>(Engine::Get().GetWidth())),
		height(static_cast<float>(Engine::Get().GetHeight())),
		nearDistance(nearDistance),
		farDistance(farDistance)
	{
		Matrix4 inverseTranslation = Matrix4::Translation(transform->position * -1.0f);
		Matrix4 rotation = Matrix4::Rotation(transform->rotation);

		viewMatrix = inverseTranslation * Matrix4::Inverse(rotation);

		projectionMatrix = Matrix4::Perspective(fieldOfView, width, height, nearDistance, farDistance);
	}
	
	CameraActor::~CameraActor()
	{
	}

	void CameraActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		// 위치 변환 행렬의 역벽환을 위해 * -1.0f를 해줌
		Matrix4 inverseTranslation = Matrix4::Translation(transform->position * -1.0f);
		Matrix4 rotation = Matrix4::Rotation(transform->rotation);

		viewMatrix = inverseTranslation * Matrix4::Inverse(rotation);
	}

	void CameraActor::Draw()
	{
		Actor::Draw();

		Renderer::Get().UpdateCameraMatrix(viewMatrix, projectionMatrix, transform->position);
	}
}