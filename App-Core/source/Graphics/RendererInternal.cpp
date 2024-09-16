#include "Graphics/RendererInternal.h"
#include "Core/Log.h"
#include "Graphics/Shader.h"

#include "Core/Application.h"
#include "Core/Base.h"

#include <glad/glad.h>

/*************************** Vertex Array ***************************/
VertexArray CreateVertexArray()
{
    VertexArray vao;
    glGenVertexArrays(1, &vao.id);

    return vao;
}

void VertexArray::Bind() { glBindVertexArray(id); }
void VertexArray::Unbind() { glBindVertexArray(0); }

void VertexArray::SetAttributes(u8 location, u8 numElements, u64 offset)
{
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, numElements, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
}

/*************************** Vertex Buffer ***************************/
VertexBuffer CreateVertexBuffer()
{
    VertexBuffer vbo;
    glGenBuffers(1, &vbo.id);

    return vbo;
}

void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }
void VertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
void VertexBuffer::SetData(float* vertices, u64 size) { glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); }

/*************************** Index Buffer ***************************/
IndexBuffer CreateIndexBuffer()
{
    IndexBuffer ebo;
    glGenBuffers(1, &ebo.id);

    return ebo;
}

void IndexBuffer::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
void IndexBuffer::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void IndexBuffer::SetData(u32* indices, u64 size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

/*************************** Internal Render State ***************************/
InternalRenderState CreateInternalRenderState()
{
    InternalRenderState renderState;
    renderState.primaryCamera = NULL;

    return renderState;
}

void RenderInitShaders(InternalRenderState* renderState)
{
    // Create default shader and set uniform locations
    renderState->defaultShader = CreateShader("assets/shaders/default_vs.glsl", "assets/shaders/default_fs.glsl");

    if (renderState->defaultShader.id == 0)
    {
        INFO("Failed to init default shader... Exiting the program!");
        App.isRunning = false;
        return;
    }

    renderState->defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE] =
        GetUniformLocation(renderState->defaultShader, "material.diffuseMap");
    renderState->defaultShader.uniformLocs[SHADER_LOC_COLOR_DIFFUSE] =
        GetUniformLocation(renderState->defaultShader, "material.diffuse");
    renderState->defaultShader.uniformLocs[SHADER_LOC_MATRIX_MODEL] =
        GetUniformLocation(renderState->defaultShader, "model");
    renderState->defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW] =
        GetUniformLocation(renderState->defaultShader, "view");
    renderState->defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION] =
        GetUniformLocation(renderState->defaultShader, "projection");
}
