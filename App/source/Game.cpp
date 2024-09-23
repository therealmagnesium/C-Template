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

#include <UI/UI.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <memory>

static Camera camera;
static DirectionalLight directionalLight;
static Spotlight spotlight;
static std::shared_ptr<Entity> kamek;
static std::shared_ptr<Entity> daisy;
static std::shared_ptr<Entity> man;

void GameState::OnCreate()
{
    camera = CreateCamera(glm::vec3(-2.f, 0.f, 7.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    camera.moveSpeed = 6.f;
    SetPrimaryCamera(&camera);

    Renderer.clearColor = {0.08f, 0.08f, 0.10f, 1.f};

    directionalLight = CreateDirectionalLight(glm::vec3(-0.5f, -0.8f, -0.7f), glm::vec3(0.93, 0.9, 0.71),
                                              Renderer.state.defaultShader);
    /*
    spotlight =
        CreateSpotlight(camera.position, camera.direction, glm::vec3(0.93, 0.9, 0.71), Renderer.state.defaultShader);*/

    kamek = entityManager.AddEntity("Kamek");
    kamek->AddComponent<TransformComponent>();
    kamek->AddComponent<ModelComponent>("assets/models/kamek.obj");

    daisy = entityManager.AddEntity("Daisy");
    daisy->AddComponent<TransformComponent>(glm::vec3(-4.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f));
    daisy->AddComponent<ModelComponent>("assets/models/daisy.obj");

    man = entityManager.AddEntity("Cheese Man");
    man->AddComponent<TransformComponent>(glm::vec3(-2.f, 3.f, -3.f), glm::vec3(0.f), glm::vec3(1.f));
    man->AddComponent<ModelComponent>("assets/models/man.obj");
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

    /*
    UpdateSpotlight(spotlight);
    spotlight.position = camera.position;
    spotlight.direction = camera.direction;*/
}

void GameState::OnRender() {}

void GameState::OnRenderUI()
{
    ImGui::DockSpaceOverViewport();
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
        for (u64 i = 0; i < entityManager.GetEntityCount(); i++)
        {
            std::shared_ptr<Entity> e = entityManager.GetEntities()[i];

            b8 isActive = e->IsActive();
            ImGui::Checkbox(TextFormat("%s active?", e->GetTag()), &isActive);
            e->SetActive(isActive);

            if (e->HasComponent<TransformComponent>())
            {
                TransformComponent& tc = e->GetComponent<TransformComponent>();
                ImGui::DragFloat3(TextFormat("%s position", e->GetTag()), glm::value_ptr(tc.position), 0.01f);
                ImGui::DragFloat3(TextFormat("%s rotation", e->GetTag()), glm::value_ptr(tc.rotation), 0.1f);
                ImGui::DragFloat3(TextFormat("%s scale", e->GetTag()), glm::value_ptr(tc.scale), 0.01f);
            }

            if (e->HasComponent<ModelComponent>())
            {
                ModelComponent& mc = e->GetComponent<ModelComponent>();
                ImGui::Text("%s mesh count: %ld", e->GetTag(), mc.model.meshes.size());
                ImGui::Text("%s material count: %ld", e->GetTag(), mc.model.materials.size());
            }
        }
    }
    ImGui::End();

    ImGui::Begin("Viewport");
    {
        u64 texId = (u64)App.framebuffer.colorAttachment;
        ImGui::Image((void*)texId, {(float)App.window.width, (float)App.window.height}, {0.f, 1.f}, {1.f, 0.f});
    }
    ImGui::End();
}

void GameState::OnShutdown() {}
