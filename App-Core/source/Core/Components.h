#pragma once
#include "Graphics/Model.h"
#include <glm/glm.hpp>

struct TransformComponent
{
    b8 enabled = false;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    TransformComponent()
    {
        position = glm::vec3(0.f);
        rotation = glm::vec3(0.f);
        scale = glm::vec3(1.f);
    }

    TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }
};

struct ModelComponent
{
    b8 enabled = false;
    b8 culling = true;
    Model model;

    ModelComponent() = default;
    ModelComponent(const char* path) { model = LoadModel(path); }
};
