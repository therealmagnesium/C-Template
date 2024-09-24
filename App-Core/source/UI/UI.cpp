#include "UI/UI.h"
#include "Core/Application.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

void InitUIContext(const Window& window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(window.handle, window.glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void HandleUIEvents(const SDL_Event* event)
{
    if (event)
        ImGui_ImplSDL2_ProcessEvent(event);
}

ImVec2 GetLargestViewportSize()
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    windowSize.x -= ImGui::GetScrollX();
    windowSize.y -= ImGui::GetScrollY();

    float aspect = (float)App.window.width / App.window.height;
    float aspectWidth = windowSize.x;
    float aspectHeight = aspectWidth / aspect;

    if (aspectHeight > windowSize.y)
    {
        aspectHeight = windowSize.y;
        aspectWidth = aspectHeight * aspect;
    }
    return ImVec2(aspectWidth, aspectHeight);
}

ImVec2 GetCenteredViewportPosition(ImVec2 aspectSize)
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    windowSize.x -= ImGui::GetScrollX();
    windowSize.y -= ImGui::GetScrollY();

    ImVec2 viewportPosition;
    viewportPosition.x = (windowSize.x / 2.f) - (aspectSize.x / 2.f);
    viewportPosition.y = (windowSize.y / 2.f) - (aspectSize.y / 2.f);
    viewportPosition.x += ImGui::GetCursorPosX();
    viewportPosition.y += ImGui::GetCursorPosY();

    return viewportPosition;
}

void BeginUIFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void EndUIFrame() { ImGui::Render(); }

void DrawFinalUIContext()
{
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

void ShutdownUI()
{
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}
