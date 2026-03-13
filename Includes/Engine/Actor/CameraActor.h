#pragma once
#include "actor.h"
#include "Math/Matrix4.h"

namespace Craft
{
	class CRAFT_API CameraActor : public Actor
	{
	public:
		CameraActor();
		~CameraActor();

		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

	private:
		Matrix4 cameraMatrix;
	};
}

