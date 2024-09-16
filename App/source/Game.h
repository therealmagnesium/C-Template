#pragma once
#include <Core/Base.h>

struct Game
{
    void (*OnCreate)(void);
    void (*OnUpdate)(void);
    void (*OnRender)(void);
    void (*OnRenderUI)(void);
    void (*OnShutdown)(void);
};

Game SetupGame();
