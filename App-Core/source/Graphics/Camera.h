#pragma once
#include "Core/Base.h"
#include <glm/glm.hpp>

enum CameraType
{
    CAMERA_FREE = 0,
    CAMERA_ORBITAL,
    CAMERA_TYPE_COUNT,
};

struct Camera
{
    float fov;
    float pitch;
    float yaw;
    float moveSpeed;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 up;

    glm::mat4 view;
    glm::mat4 projection;
};

/*!
 * @brief Creates a new camera, can be set to primary camera with SetPrimaryCamera(Camera*)
 * @param[in] position - The starting position of the camera in world coordinates
 * @param[in] up - A normalized vector, which defines which direction is up for the camera
 * @param[in] fov - Specifically, the field of view for the camera's pitch (fovy)
 */
Camera CreateCamera(glm::vec3 position, glm::vec3 up, float fov);

/*!
 * @brief Updates the primary camera with a camera type
 * @param[in] type - The way the camera should behave when updating (freelook, orbital)
 */
void UpdateCamera(CameraType type);

// @brief Update the primary camera's matrices
void UpdateCameraMatrices();

// @brief Log information about a camera
void LogCameraInfo(const Camera& camera);
