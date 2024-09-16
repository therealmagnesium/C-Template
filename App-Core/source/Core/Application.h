#pragma once
#include "Core/Base.h"
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

    void (*OnCreate)(void);
    void (*OnUpdate)(void);
    void (*OnRender)(void);
    void (*OnRenderUI)(void);
    void (*OnShutdown)(void);
};

struct AppState
{
    b8 isRunning;
    b8 isDebugEnabled;
    Window window;
    GameState* game;
};

extern AppState App;

void CreateApplication(GameState* game);
void RunApplication();
