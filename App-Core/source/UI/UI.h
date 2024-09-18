#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"

#include <SDL2/SDL_events.h>

void InitUIContext(const Window& window);
void HandleUIEvents(const SDL_Event* event);
void BeginUIFrame();
void EndUIFrame();
void DrawFinalUIContext();
void ShutdownUI();
