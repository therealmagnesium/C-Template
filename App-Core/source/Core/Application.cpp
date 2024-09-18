#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"

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
    App.window = CreateWindow(&game->info);
    App.isDebugEnabled = false;

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
        App.game->OnUpdate();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        App.game->OnRenderUI();
        ImGui::Render();

        Renderer.BeginDrawing();
        {
            App.game->OnRender();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
                SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
            }
        }
        Renderer.EndDrawing();
        UpdateTimeLate();
    }

    App.game->OnShutdown();
    App.window.Close();

    INFO("Successfully ended the application!");
}
