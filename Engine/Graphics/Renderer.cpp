#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include "StaticMesh.h"
#include "Shader/Shader.h"
#include "Math/Transform.h"
#include <d3dcompiler.h>
#include <cassert>

namespace Craft
{
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer()
	{
		assert(!instance);
		instance = this;
	}

	Renderer::~Renderer()
	{
		SafeRelease(cameraBuffer);
	}

	// 초기화.
	void Renderer::Initialize()
	{
		auto& device = GraphicsContext::Get().GetDevice();

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(Matrix4);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ThrowIfFailed(device.CreateBuffer(&bufferDesc, nullptr, &cameraBuffer), L"Failed to create camera buffer");
	}

	void Renderer::Submit(
		std::shared_ptr<StaticMesh> mesh,
		std::shared_ptr<Shader> shader,
		std::shared_ptr<Transform> transform)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.shader = shader;
		command.transform = transform;

		renderQueue.emplace_back(command);
	}

	void Renderer::UpdateCameraMatrix(const Matrix4& viewMatrix, const Matrix4& projectionMatrix)
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();
		D3D11_MAPPED_SUBRESOURCE resource = {};
		ThrowIfFailed(context.Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource),
			L"Failed to map camera buffer");

		Matrix4 cameraMatirxRef = Matrix4::Transpose(viewMatrix * projectionMatrix);
		memcpy(resource.pData, &cameraMatirxRef, sizeof(Matrix4));
		context.Unmap(cameraBuffer, 0);
	}

	// DrawCall 발생 처리.
	// -> 렌더링 파이프라인 실행(구동).
	void Renderer::DrawScene()
	{
		// 바인딩.
		// -> 셰이더 각 단계에 필요한 정보 전달 및 설정.
		// State 설정.
		auto& context = GraphicsContext::Get().GetDeviceContext();

		// 렌더 커맨드 가져오기.
		for (const RenderCommand& command : renderQueue)
		{
			//auto vertexBuffer = command.mesh->GetVertexBuffer();
			//uint32_t stride = command.mesh->GetStride();
			//uint32_t offset = 0;

			/*context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			context.IASetIndexBuffer(command.mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);*/
			//context.IASetInputLayout(command.shader->GetInputLayout());
			// 점 3개씩 잘라서 읽고, 삼각형을 만들어주는 모드.
			/*context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);*/

			// 셰이더 설정.
			//context.VSSetShader(command.shader->GetVertexShader(), nullptr, 0);
			//context.PSSetShader(command.shader->GetPixelShader(), nullptr, 0);

			// 드로우 콜.
			// 렌더링 파이프라인 동작.

			command.mesh->Bind();
			command.shader->Bind();
			command.transform->Bind();
			
			context.VSSetConstantBuffers(1, 1, &cameraBuffer);
			context.DrawIndexed(command.mesh->GetIndexCount(), 0, 0);
		}

		renderQueue.clear();
	}

	Renderer& Renderer::Get()
	{
		assert(instance);
		return *instance;
	}
}