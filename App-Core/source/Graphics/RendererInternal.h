#pragma once
#include "Core/Base.h"

#include "Graphics/Camera.h"
#include "Graphics/Shader.h"

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

struct VertexArray
{
    u32 id;

    void Bind();
    void Unbind(void);
    void SetAttributes(u8 location, u8 numElements, u64 offset);
};

struct VertexBuffer
{
    u32 id;

    void Bind();
    void Unbind(void);
    void SetData(float* vertices, u64 size);
};

struct IndexBuffer
{
    u32 id;

    void Bind();
    void Unbind(void);
    void SetData(u32* indices, u64 size);
};

struct InternalRenderState
{
    Shader defaultShader;
    Camera* primaryCamera;
};

VertexArray CreateVertexArray();
VertexBuffer CreateVertexBuffer();
IndexBuffer CreateIndexBuffer();
InternalRenderState CreateInternalRenderState();

void RenderInitShaders(InternalRenderState* renderState);
