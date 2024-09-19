#include "Game.h"
#include "Core/Entity.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>
#include <Core/Time.h>

#include <Graphics/Camera.h>
#include <Graphics/Light.h>
#include <Graphics/Model.h>
#include <Graphics/Renderer.h>
#include <Graphics/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

static Camera camera;
static DirectionalLight directionalLight;
static Entity entity;

void GameState::OnCreate()
{
    camera = CreateCamera(glm::vec3(-2.f, 0.f, 7.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    camera.moveSpeed = 6.f;
    SetPrimaryCamera(&camera);

    Renderer.clearColor = {0.08f, 0.08f, 0.10f, 1.f};

    directionalLight = CreateDirectionalLight(glm::vec3(-0.5f, -0.8f, -0.7f), glm::vec3(0.93, 0.9, 0.71),
                                              Renderer.state.defaultShader);

    entity = entityManager.AddEntity("Entity");
    entity.AddComponent<TransformComponent>();
    entity.AddComponent<ModelComponent>("assets/models/daisy.obj");
}

void GameState::OnUpdate()
{
    if (IsKeyPressed(KEY_F9))
        App.isDebugEnabled = !App.isDebugEnabled;

    if (!App.isDebugEnabled)
        UpdateCamera(CAMERA_FREE);

    if (IsKeyPressed(KEY_C))
        LogCameraInfo(camera);

    UpdateDirectionalLight(directionalLight);
}

void GameState::OnRender()
{
    TransformComponent& tc = entity.GetComponent<TransformComponent>();
    ModelComponent& mc = entity.GetComponent<ModelComponent>();

    if (entity.IsActive())
        Renderer.DrawModel(mc.model, tc.position, tc.rotation, tc.scale);
}

void GameState::OnRenderUI()
{
    if (App.isDebugEnabled)
    {
        ImGui::Begin("Lighting Menu");
        {
            ImGui::DragFloat3("Light direction", glm::value_ptr(directionalLight.direction), 0.01f, -1.f, 1.f);
            ImGui::DragFloat("Ambient intensity", &directionalLight.ambientIntensity, 0.01f);
            ImGui::DragFloat("Diffuse intensity", &directionalLight.diffuseIntensity, 0.01f);
            ImGui::DragFloat("Specular intensity", &directionalLight.specularIntensity, 0.01f);
            ImGui::ColorPicker3("Light color", glm::value_ptr(directionalLight.color));
        }
        ImGui::End();

        ImGui::Begin("Entity Heirarchy");
        {
            TransformComponent& entityTransform = entity.GetComponent<TransformComponent>();
            b8 entityIsActive = entity.IsActive();

            ImGui::Checkbox("Entity active?", &entityIsActive);
            ImGui::DragFloat3("Entity position", glm::value_ptr(entityTransform.position), 0.01f);
            ImGui::DragFloat3("Entity rotation", glm::value_ptr(entityTransform.rotation), 0.1f);
            ImGui::DragFloat3("Entity scale", glm::value_ptr(entityTransform.scale), 0.01f);

            entity.SetActive(entityIsActive);
        }
        ImGui::End();
    }
}

void GameState::OnShutdown() {}
