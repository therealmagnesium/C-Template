#pragma once
#include "Core/Base.h"
#include "Core/Application.h"
#include "Core/Log.h"

extern void CreateGameState(GameState* gameState);

int main(int argc, char* argv[])
{
    GameState gameState;
    gameState.OnCreate = NULL;
    gameState.OnUpdate = NULL;
    gameState.OnRender = NULL;
    gameState.OnRenderUI = NULL;
    gameState.OnShutdown = NULL;

    CreateGameState(&gameState);
    if (!gameState.OnCreate || !gameState.OnUpdate || !gameState.OnRender || !gameState.OnRenderUI ||
        !gameState.OnShutdown)
    {
        FATAL("The game's function pointers must be assigned!");
        return -1;
    }

    CreateApplication(&gameState);
    RunApplication();

    return 0;
}
