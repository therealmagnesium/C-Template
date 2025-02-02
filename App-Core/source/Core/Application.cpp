#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include "Graphics/Framebuffer.h"
#include "Graphics/Renderer.h"
#include "Graphics/Window.h"

#include "UI/UI.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

AppState App;
static b8 initialized = false;

void CreateApplication(GameState* game)
{
    if (initialized)
    {
        ERROR("CreateApplication(AppInfo*) can only be called once!");
        return;
    }

    InitLogging();
    InitTimeState(60);

    App.isRunning = true;
    App.game = game;
    App.isDebugEnabled = false;
    App.window = CreateWindow(&game->info);

    FramebufferSpecification fbSpec;
    fbSpec.width = App.window.width;
    fbSpec.height = App.window.height;
    App.framebuffer = CreateFramebuffer(fbSpec);

    InitRenderer();

    App.game->OnCreate();

    if (!Renderer.state.primaryCamera)
        WARN("No primary camera set, nothing may be drawn to the window!");

    initialized = true;

    INFO("Successfully created the application!");
    INFO("GPU vendor - %s", glGetString(GL_VENDOR));
    INFO("Renderer - %s", glGetString(GL_RENDERER));
    INFO("OpenGL version - %s", glGetString(GL_VERSION));
}

void RunApplication()
{
    while (App.isRunning)
    {
        App.window.HandleEvents();

        App.game->entityManager.Update();
        App.game->OnUpdate();

        BeginUIFrame();
        {
            App.game->OnRenderUI();
        }
        EndUIFrame();

        App.framebuffer.Bind();
        {
            Renderer.BeginDrawing();
            App.game->OnRender();
            App.game->entityManager.DrawEntities();
        }
        App.framebuffer.Unbind();

        Renderer.BeginDrawing();
        {
            DrawFinalUIContext();
        }
        Renderer.EndDrawing();

        UpdateTimeLate();
    }

    App.game->OnShutdown();
    App.window.Close();

    INFO("Successfully ended the application!");
}
