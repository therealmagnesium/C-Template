#pragma once
#include "Core/Base.h"
#include "Graphics/RendererInternal.h"
#include <vector>

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    u32 materialIndex;

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    Mesh();
    Mesh(Vertex* vertices, u64 vertexCount, u32* indices, u64 indexCount);

    void Create(Vertex* vertices, u64 vertexCount, u32* indices, u64 indexCount);
};
