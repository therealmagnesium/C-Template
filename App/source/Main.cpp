#include "Game.h"

#include <Core/Base.h>
#include <Core/EntryPoint.h>

void CreateGameState(GameState* gameState)
{
    // Set application info
    gameState->info.screenWidth = 1280;
    gameState->info.screenHeight = 720;
    gameState->info.title = "C++ Template";
}
