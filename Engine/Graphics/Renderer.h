#pragma once

#include "Math/Matrix4.h"
#include <vector>
#include <d3d11.h>
#include <memory>

namespace Craft
{
	class StaticMesh;
	class Shader;
	class Transform;
	struct RenderCommand
	{
		std::shared_ptr<StaticMesh> mesh;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Transform> transform;
	};

	struct CameraData
	{
		Matrix4 matrix;
		Vector3 position;
		float padding;
	};

	// DrawCall ´ã´ç
	// RHI - Render Hardware Interface
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Initialize();
		void Submit(
			std::shared_ptr<StaticMesh> mesh,
			std::shared_ptr<Shader> shader,
			std::shared_ptr<Transform> transform);

		void UpdateCameraMatrix(
			const Matrix4& viewMatrix,
			const Matrix4& projectionMatrix,
			const Vector3& position);

		void DrawScene();
		static Renderer& Get();

	private:
		std::vector<RenderCommand> renderQueue;
		ID3D11Buffer* cameraBuffer = nullptr;
		static Renderer* instance;
	};
}

