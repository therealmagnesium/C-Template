#include "Game.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/IO.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>
#include <Core/Time.h>

#include <Graphics/Camera.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <Graphics/Renderer.h>
#include <Graphics/Texture.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

static Camera camera;
static Mesh mesh;
static Material material;
static Model model;

static void OnCreate()
{
    camera = CreateCamera(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    SetPrimaryCamera(&camera);

    Renderer.clearColor = {0.08f, 0.08f, 0.10f, 1.f};

    Vertex vertices[4];
    vertices[0].position = {0.5f, 0.5f, 0.f};
    vertices[1].position = {0.5f, -0.5f, 0.f};
    vertices[2].position = {-0.5f, -0.5f, 0.f};
    vertices[3].position = {-0.5f, 0.5f, 0.f};

    for (u8 i = 0; i < 4; i++)
        vertices[i].normal = {0.f, 0.f, -1.f};

    vertices[0].texCoord = {1.f, 1.f};
    vertices[1].texCoord = {1.f, 0.f};
    vertices[2].texCoord = {0.f, 0.f};
    vertices[3].texCoord = {0.f, 1.f};

    u32 indices[6] = {
        0, 1, 3, // i0
        1, 2, 3, // i1
    };

    mesh.Create(vertices, LEN(vertices), indices, LEN(indices));
    material.shader = Renderer.state.defaultShader;
    material.maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/texel_checker.png", RGBA);
    material.maps[MATERIAL_MAP_DIFFUSE].color = {1.f, 1.f, 1.f, 1.f};

    model = LoadModel("assets/models/backpack/backpack.obj");
}

static void OnUpdate() { UpdateCamera(CAMERA_FREE); }

static void OnRender()
{
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, {0.f, 0.f, -3.f});
    model = glm::rotate(model, glm::radians(-45.f), {1.f, 0.f, 0.f});
    model = glm::rotate(model, glm::radians(0.f), {0.f, 1.f, 0.f});
    model = glm::rotate(model, glm::radians(0.f), {0.f, 0.f, 1.f});
    model = glm::scale(model, {2.f, 2.f, 1.f});
    Renderer.DrawMesh(mesh, model, material);

    // Renderer.DrawModel(model, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
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
