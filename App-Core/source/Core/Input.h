#pragma once
#include "Core/Base.h"
#include "Core/KeyCodes.h"

#include <glm/glm.hpp>

enum InputAxis
{
    INPUT_AXIS_HORIZONTAL = 0,
    INPUT_AXIS_VERTICAL,
};

struct MouseInputState
{
    glm::vec2 position;
    b8 held;
    b8 clicked;
    u32 button;
};

struct KeyboardInputState
{
    b8 held[KEY_COUNT];
    b8 pressed[KEY_COUNT];
};

struct InputState
{
    MouseInputState mouse;
    KeyboardInputState key;
};

extern InputState Input;

bool IsMouseDown(MouseButton button);
bool IsMouseClicked(MouseButton button);
bool IsKeyDown(u32 scancode);
bool IsKeyPressed(u32 scancode);
float GetInputAxis(InputAxis axis);
float GetInputAxisAlt(InputAxis axis);
