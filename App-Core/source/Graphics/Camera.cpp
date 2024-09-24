#include "Graphics/Camera.h"
#include "Core/KeyCodes.h"
#include "Graphics/Renderer.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera CreateCamera(glm::vec3 position, glm::vec3 up, float fov)
{
    Camera camera;
    camera.position = position;
    camera.up = up;
    camera.target = {0.f, 0.f, 0.f};
    camera.fov = fov;
    camera.moveSpeed = 8.f;
    camera.isLocked = false;

    camera.direction = camera.target - camera.position;
    camera.direction = glm::normalize(camera.direction);

    camera.view = glm::mat4(1.f);
    camera.projection = glm::mat4(1.f);

    camera.pitch = 0.f;
    camera.yaw = -90.f;

    return camera;
}

static void UpdateCameraFree()
{
    Camera* camera = Renderer.state.primaryCamera;

    static glm::vec2 lastMousePosition;
    glm::vec2 mouseOffset = {0.f, 0.f};

    if (IsMouseDown(MOUSE_BUTTON_LEFT))
    {
        if (IsMouseClicked(MOUSE_BUTTON_LEFT))
        {
            lastMousePosition.x = Input.mouse.position.x;
            lastMousePosition.y = Input.mouse.position.y;
        }

        mouseOffset.x = Input.mouse.position.x - lastMousePosition.x;
        mouseOffset.y = lastMousePosition.y - Input.mouse.position.y;
        lastMousePosition.x = Input.mouse.position.x;
        lastMousePosition.y = Input.mouse.position.y;

        mouseOffset.x *= 0.1f;
        mouseOffset.y *= 0.1f;
    }

    // Apply the mouse offset by the pitch and yaw rotation
    camera->yaw += mouseOffset.x;
    camera->pitch += mouseOffset.y;

    // Cap the camera's pitch
    if (camera->pitch > 90.f)
        camera->pitch = 90.f;
    if (camera->pitch < -90.f)
        camera->pitch = -90.f;

    // Calculate the camera's direction using some trig
    camera->direction[0] = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->direction[1] = sin(glm::radians(camera->pitch));
    camera->direction[2] = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->direction = glm::normalize(camera->direction);

    // Calculate the camera's right vector, by normalizing the cross product between the forward and up vector
    glm::vec3 camRight = glm::cross(camera->direction, camera->up);
    camRight = glm::normalize(camRight);

    // Walk forward
    if (IsKeyDown(KEY_W))
        camera->position += camera->direction * camera->moveSpeed * Time.delta;

    // Walk backward
    if (IsKeyDown(KEY_S))
        camera->position -= camera->direction * camera->moveSpeed * Time.delta;

    // Walk right
    if (IsKeyDown(KEY_D))
        camera->position += camRight * camera->moveSpeed * Time.delta;

    // Walk left
    if (IsKeyDown(KEY_A))
        camera->position -= camRight * camera->moveSpeed * Time.delta;

    // Fly upwards
    if (IsKeyDown(KEY_SPACE))
        camera->position += camera->up * camera->moveSpeed * Time.delta;

    // Fly downwards
    if (IsKeyDown(KEY_LEFT_CTRL))
        camera->position -= camera->up * camera->moveSpeed * Time.delta;
}

static void UpdateCameraOrbital() {}

void UpdateCamera(CameraType type)
{
    if (Renderer.state.primaryCamera && !Renderer.state.primaryCamera->isLocked)
    {
        switch (type)
        {
            case CAMERA_FREE:
            {
                UpdateCameraFree();
                break;
            }

            case CAMERA_ORBITAL:
            {
                UpdateCameraOrbital();
                break;
            }

            default:
                break;
        }
    }
}

void UpdateCameraMatrices()
{
    Camera* camera = Renderer.state.primaryCamera;

    if (camera)
    {
        float aspect = (float)App.window.width / App.window.height;

        camera->view = glm::lookAt(camera->position, camera->position + camera->direction, camera->up);
        camera->projection = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.f);

        Renderer.state.defaultShader.Bind();
        Renderer.state.defaultShader.SetVec3(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_VECTOR_VIEW],
                                             glm::value_ptr(camera->position));
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                                             glm::value_ptr(camera->view));
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                                             glm::value_ptr(camera->projection));
        Renderer.state.defaultShader.Unbind();
    }
}

void LogCameraInfo(const Camera& camera)
{
    INFO("Camera position: " V3_FMT, V3_OPEN(camera.position));
    INFO("Camera target: " V3_FMT, V3_OPEN(camera.target));
    INFO("Camera up: " V3_FMT, V3_OPEN(camera.up));
    INFO("Camera direction: " V3_FMT, V3_OPEN(camera.direction));
    INFO("Camera fov: %.1f", camera.fov);
}
