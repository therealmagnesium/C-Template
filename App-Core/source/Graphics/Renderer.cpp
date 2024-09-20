#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"
#include "Graphics/RendererInternal.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

RenderState Renderer;
static bool initialized = false;

void InitRenderer()
{
    if (initialized)
    {
        ERROR("Renderer is already initialized!");
        return;
    }

    Renderer.clearColor = {1.f, 1.f, 1.f, 1.f};
    Renderer.state = CreateInternalRenderState();
    RenderInitShaders(&Renderer.state);

    initialized = true;
}

void RenderState::BeginDrawing()
{
    glClearColor(V4_OPEN(Renderer.clearColor));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateCameraMatrices();
}

void RenderState::EndDrawing() { SDL_GL_SwapWindow(App.window.handle); }

void RenderState::DrawMesh(Mesh& mesh, glm::mat4& transform, Material& material)
{
    if (material.shader.id == 0)
        material.shader = state.defaultShader;

    material.shader.Bind();

    material.shader.SetMat4(material.shader.uniformLocs[SHADER_LOC_MATRIX_MODEL], glm::value_ptr(transform));

    glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform));
    material.shader.SetMat4(material.shader.uniformLocs[SHADER_LOC_MATRIX_NORMAL], glm::value_ptr(normalMatrix));

    material.shader.SetVec3(material.shader.uniformLocs[SHADER_LOC_COLOR_AMBIENT], glm::value_ptr(material.ambient));
    material.shader.SetVec3(material.shader.uniformLocs[SHADER_LOC_COLOR_DIFFUSE],
                            glm::value_ptr(material.maps[MATERIAL_MAP_DIFFUSE].color));
    material.shader.SetVec3(material.shader.uniformLocs[SHADER_LOC_COLOR_SPECULAR],
                            glm::value_ptr(material.maps[MATERIAL_MAP_SPECULAR].color));

    for (u32 i = MATERIAL_MAP_DIFFUSE; i < MATERIAL_MAP_COUNT; i++)
    {
        material.shader.SetInt(material.shader.uniformLocs[i], i);

        if (material.maps[i].texture.isValid)
            BindTexture(material.maps[i].texture, i);
    }

    mesh.vertexArray.Bind();
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);
    mesh.vertexArray.Unbind();

    UnbindTexture();
    material.shader.Unbind();
}

void RenderState::DrawModel(Model& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    model.transform = glm::mat4(1.f);
    model.transform = glm::translate(model.transform, position);
    model.transform = glm::rotate(model.transform, glm::radians(rotation.x), {1.f, 0.f, 0.f});
    model.transform = glm::rotate(model.transform, glm::radians(rotation.y), {0.f, 1.f, 0.f});
    model.transform = glm::rotate(model.transform, glm::radians(rotation.z), {0.f, 0.f, 1.f});
    model.transform = glm::scale(model.transform, scale);

    Material defaultMaterial;
    defaultMaterial.shader = state.defaultShader;
    defaultMaterial.maps[MATERIAL_MAP_DIFFUSE].color = {1.f, 1.f, 1.f};

    for (u64 i = 0; i < model.meshes.size(); i++)
        this->DrawMesh(model.meshes[i], model.transform, model.materials[model.meshes[i].materialIndex]);
}
