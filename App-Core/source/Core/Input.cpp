#include "Core/Input.h"
#include "Core/Base.h"

InputState Input;

bool IsMouseDown(MouseButton button) { return Input.mouse.held && Input.mouse.button == button; }
bool IsMouseClicked(MouseButton button) { return Input.mouse.clicked && Input.mouse.button == button; }
bool IsKeyDown(u32 scancode) { return Input.key.held[scancode] == true; }
bool IsKeyPressed(u32 scancode) { return Input.key.pressed[scancode] == true; }

float GetInputAxis(InputAxis axis)
{
    float val = 0.f;

    switch (axis)
    {
        case INPUT_AXIS_HORIZONTAL:
        {
            val = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
            break;
        }

        case INPUT_AXIS_VERTICAL:
        {
            val = IsKeyDown(KEY_UP) - IsKeyDown(KEY_DOWN);
            break;
        }
    }

    return val;
}

float GetInputAxisAlt(InputAxis axis)
{
    float val = 0.f;

    switch (axis)
    {
        case INPUT_AXIS_HORIZONTAL:
        {
            val = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
            break;
        }

        case INPUT_AXIS_VERTICAL:
        {
            val = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
            break;
        }
    }

    return val;
}
