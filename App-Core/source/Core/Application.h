#pragma once
#include "Core/Base.h"
#include "Core/EntityManager.h"

#include "Graphics/Framebuffer.h"
#include "Graphics/Window.h"

struct AppInfo
{
    u32 screenWidth;
    u32 screenHeight;
    const char* title;
};

struct GameState
{
    AppInfo info;
    EntityManager entityManager;

    void OnCreate();
    void OnUpdate();
    void OnRender();
    void OnRenderUI();
    void OnShutdown();
};

struct AppState
{
    b8 isRunning;
    b8 isDebugEnabled;
    Framebuffer framebuffer;
    Window window;
    GameState* game;
};

extern AppState App;

void CreateApplication(GameState* game);
void RunApplication();
