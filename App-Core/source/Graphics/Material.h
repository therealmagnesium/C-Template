#pragma once
#include "Core/Base.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <glm/glm.hpp>

enum MaterialMapIndex
{
    MATERIAL_MAP_DIFFUSE = 0,
    MATERIAL_MAP_SPECULAR,
    MATERIAL_MAP_COUNT
};

struct MaterialMap
{
    float value;
    glm::vec3 color;
    Texture texture;
};

struct Material
{
    glm::vec3 ambient;
    Shader shader;
    MaterialMap maps[MATERIAL_MAP_COUNT];
};
