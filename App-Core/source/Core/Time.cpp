#include "Core/Time.h"
#include "Core/Application.h"
#include <SDL2/SDL_timer.h>

TimeState Time;

void InitTimeState(u32 frameRate)
{
    Time.frameRate = frameRate;
    Time.frameDelay = 1000.f / frameRate;
}

void UpdateTime()
{
    Time.now = SDL_GetTicks();
    Time.delta = (Time.now - Time.last) / 1000.f;
    Time.last = Time.now;
    ++Time.frameCount;

    if (Time.now - Time.lastFrame >= 1000.f)
    {
        Time.frameRate = Time.frameCount;
        Time.frameCount = 0;
        Time.lastFrame = Time.now;
    }
}

void UpdateTimeLate()
{
    // Get how long it took to render a frame
    Time.frameTime = (float)SDL_GetTicks() - Time.now;

    if (!App.window.vsync)
    {
        // Cap the frame rate if we rendered the frame too fast
        if (Time.frameDelay > Time.frameTime)
            SDL_Delay(Time.frameDelay - Time.frameTime);
    }
}
