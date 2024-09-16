#pragma once
#include "Core/Base.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"

#include <glm/glm.hpp>
#include <vector>

struct Model
{
    glm::mat4 transform;
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
};

Model LoadModel(const char* path);
