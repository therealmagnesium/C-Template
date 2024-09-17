#include "Game.h"

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
#include <glm/ext/matrix_transform.hpp>

static Camera camera;
static DirectionalLight directionalLight;
static Model man;
static Model toad;

static void OnCreate()
{
    camera = CreateCamera(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    SetPrimaryCamera(&camera);

    Renderer.clearColor = {0.08f, 0.08f, 0.10f, 1.f};

    directionalLight = CreateDirectionalLight(glm::vec3(0.2f, -1.f, -0.4f), Renderer.state.defaultShader);
    man = LoadModel("assets/models/man.obj");
    toad = LoadModel("assets/models/toad.obj");
}

static void OnUpdate()
{
    UpdateCamera(CAMERA_FREE);
    UpdateDirectionalLight(directionalLight);
}

static void OnRender()
{
    Renderer.DrawModel(man, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.5f));
    Renderer.DrawModel(toad, glm::vec3(-3.f, -2.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.4f, 0.4f, 0.4f));
}

static void OnRenderUI() {}

static void OnShutdown() {}

Game SetupGame()
{
    Game game;

    game.OnCreate = OnCreate;
    game.OnUpdate = OnUpdate;
    game.OnRender = OnRender;
    game.OnRenderUI = OnRenderUI;
    game.OnShutdown = OnShutdown;

    return game;
}
