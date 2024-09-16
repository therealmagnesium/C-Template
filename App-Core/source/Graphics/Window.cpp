#include "Graphics/Window.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_video.h>
#include <glad/glad.h>

Window CreateWindow(AppInfo* info)
{
    // Setup window to be created
    Window window;
    window.width = info->screenWidth;
    window.height = info->screenHeight;
    window.title = info->title;
    window.vsync = true;
    window.fullscreen = false;
    window.handle = NULL;

    // Initialize SDL2
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        FATAL("Failed to init sdl2!");
        return (Window){};
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create the window handle
    s32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
    window.handle = SDL_CreateWindow(window.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.width,
                                     window.height, flags);

    // Check if creating the window handle failed
    if (!window.handle)
    {
        FATAL("Failed to create window!");
        return (Window){};
    }

    window.glContext = SDL_GL_CreateContext(window.handle);
    gladLoadGL();

    if (window.vsync)
        SDL_GL_SetSwapInterval(1);
    else
        SDL_GL_SetSwapInterval(0);

    return window;
}

void Window::HandleEvents()
{
    UpdateTime();

    Input.mouse.clicked = false;

    for (u32 i = 0; i < KEY_COUNT; i++)
        Input.key.pressed[i] = false;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                App.isRunning = false;
                break;
            };

            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        App.window.width = event.window.data1;
                        App.window.height = event.window.data2;
                        glViewport(0, 0, App.window.width, App.window.height);

                        INFO("Resized window to %dx%d", App.window.width, App.window.height);

                        break;
                    }
                }

                break;
            }

            case SDL_MOUSEMOTION:
            {
                Input.mouse.position.x = event.motion.x;
                Input.mouse.position.y = event.motion.y;

                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                Input.mouse.clicked = !Input.mouse.held;
                Input.mouse.held = true;
                Input.mouse.button = event.button.button;

                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                Input.mouse.clicked = false;
                Input.mouse.held = false;
                Input.mouse.button = 0;

                break;
            }

            case SDL_KEYDOWN:
            {
                u8 currentKey = event.key.keysym.scancode;
                Input.key.pressed[currentKey] = !Input.key.held[currentKey];
                Input.key.held[event.key.keysym.scancode] = true;

                break;
            }

            case SDL_KEYUP:
            {
                u8 currentKey = event.key.keysym.scancode;
                Input.key.pressed[currentKey] = false;
                Input.key.held[currentKey] = false;

                break;
            }

            default:
                break;
        }
    }

    if (IsKeyPressed(KEY_ESCAPE))
        App.isRunning = false;
}

void Window::Close()
{
    SDL_GL_DeleteContext(App.window.glContext);
    SDL_DestroyWindow(App.window.handle);
    SDL_Quit();
}
