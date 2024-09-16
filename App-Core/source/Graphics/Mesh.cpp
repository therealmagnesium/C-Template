#include "Graphics/Mesh.h"
#include "Core/Base.h"
#include "Graphics/RendererInternal.h"

Mesh::Mesh() {}

Mesh::Mesh(Vertex* vertices, u64 vertexCount, u32* indices, u64 indexCount)
{
    this->Create(vertices, vertexCount, indices, indexCount);
}

void Mesh::Create(Vertex* vertices, u64 vertexCount, u32* indices, u64 indexCount)
{
    vertexArray = CreateVertexArray();
    vertexBuffer = CreateVertexBuffer();
    indexBuffer = CreateIndexBuffer();

    this->vertices.resize(vertexCount);
    this->indices.resize(indexCount);

    for (u64 i = 0; i < vertexCount; i++)
        this->vertices[i] = vertices[i];

    for (u64 i = 0; i < indexCount; i++)
        this->indices[i] = indices[i];

    vertexArray.Bind();

    vertexBuffer.Bind();
    vertexBuffer.SetData((float*)this->vertices.data(), sizeof(Vertex) * vertexCount);

    indexBuffer.Bind();
    indexBuffer.SetData(this->indices.data(), sizeof(u32) * indexCount);

    vertexArray.SetAttributes(0, 3, 0);
    vertexArray.SetAttributes(1, 2, sizeof(float) * 3);
    vertexArray.SetAttributes(2, 3, sizeof(float) * 5);

    vertexArray.Unbind();
}
