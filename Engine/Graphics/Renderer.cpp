#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include <d3dcompiler.h>

namespace Craft
{

    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
        // TEMP: 재사용하는 렌더 커맨드 해제

        auto& command = renderQueue[0];
        SafeRelease(command.vertexBuffer);
        SafeRelease(command.indexBuffer);
        SafeRelease(command.inputLayout);
        SafeRelease(command.vertexShader);
        SafeRelease(command.pixelShader);
    }

    void Renderer::Initialize()
    {
        // TEMP: 프레임워크 구성될 때까지 임시로 재사용할 리소스 생성
        RenderCommand renderCommand;

        auto& device = GraphicsContext::Get().GetDevice();

        float vertices[] = 
        {
            0.0f, 0.5f, 0.1f,
            0.5f, -0.5f, 0.1f,
           -0.5f, -0.5f, 0.1f,
        };

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = sizeof(float) * _countof(vertices);
        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexData = {};
        vertexData.pSysMem = vertices;

        ID3D11Buffer* vertexBuffer = nullptr;
        HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
        if (FAILED(result))
        {
            __debugbreak();
            return;
        }

        uint32_t indices[] = { 0,1,2 };
        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(uint32_t) * _countof(indices);
        indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA indexData = {};
        indexData.pSysMem = indices;

        ID3D11Buffer* indexBuffer = nullptr;
        result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
        if (FAILED(result))
        {
            __debugbreak();
            return;
        }

        // 셰이더 컴파일
        // 셰이더 객체 생성

        RenderCommand command;
        command.vertexBuffer = vertexBuffer;
        command.indexBuffer = indexBuffer;
        command.indexCount = _countof(indices);
    }

    void Renderer::DrawScene()
    {
    }
}