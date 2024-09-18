#pragma once
#include "Core/Base.h"
#include "Core/Application.h"
#include "Core/Log.h"

extern void CreateGameState(GameState* gameState);

int main(int argc, char* argv[])
{
    GameState gameState;

    CreateGameState(&gameState);
    CreateApplication(&gameState);
    RunApplication();

    return 0;
}
