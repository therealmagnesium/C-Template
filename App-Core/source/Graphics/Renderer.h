#pragma once
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/RendererInternal.h"
#include "Graphics/Shader.h"

#include <glm/glm.hpp>

struct RenderState
{
    glm::vec4 clearColor;
    InternalRenderState state;

    void BeginDrawing();
    void EndDrawing();
    void DrawMesh(Mesh& mesh, glm::mat4& transform, Material& material);
    void DrawModel(Model& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
};

extern RenderState Renderer;

void InitRenderer();
inline void SetPrimaryCamera(Camera* camera) { Renderer.state.primaryCamera = camera; }
