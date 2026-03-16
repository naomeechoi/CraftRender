#include "CameraActor.h"
#include "Math/Transform.h"
#include "Graphics/Renderer.h"

namespace Craft
{
	CameraActor::CameraActor()
	{
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

		Renderer::Get().UpdateCameraMatrix(viewMatrix);
	}
}