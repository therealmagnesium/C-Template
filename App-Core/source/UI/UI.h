#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"

#include <imgui.h>
#include <SDL2/SDL_events.h>

void InitUIContext(const Window& window);
void HandleUIEvents(const SDL_Event* event);
ImVec2 GetLargestViewportSize();
ImVec2 GetCenteredViewportPosition(ImVec2 aspectSize);
void BeginUIFrame();
void EndUIFrame();
void DrawFinalUIContext();
void ShutdownUI();
