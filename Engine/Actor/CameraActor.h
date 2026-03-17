#pragma once
#include "actor.h"
#include "Math/Matrix4.h"

namespace Craft
{
	class CRAFT_API CameraActor : public Actor
	{
	public:
		CameraActor(
			float fieldOfView = 60.0f,
			float nearDistance = 0.1f,
			float farDistance = 10000.0f);
		~CameraActor();

		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

	private:
		Matrix4 viewMatrix;

		Matrix4 projectionMatrix;
		float fieldOfView = 0;
		float width = 0;
		float height = 0;
		float nearDistance = 0;
		float farDistance = 0;
	};
}

