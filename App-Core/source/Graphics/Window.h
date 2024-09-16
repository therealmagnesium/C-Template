#pragma once
#include "Core/Base.h"

#include <SDL2/SDL.h>

struct AppInfo; // Forward declaration

typedef struct Window_t
{
    u16 width;
    u16 height;
    b8 vsync;
    b8 fullscreen;
    const char* title;
    void* glContext;
    SDL_Window* handle;

    void HandleEvents(void);
    void Close(void);

} Window;

Window CreateWindow(AppInfo* info);
