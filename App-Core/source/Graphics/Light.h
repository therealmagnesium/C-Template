#include "Core/Base.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <glm/glm.hpp>

struct DirectionalLight
{
    glm::vec3 direction;
    glm::vec3 color;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    enum LightUniformLocation
    {
        LOC_DIRECTION = 0,
        LOC_COLOR,
        LOC_AMBIENT_INTENSITY,
        LOC_DIFFUSE_INTENSITY,
        LOC_SPECULAR_INTENSITY,
        LOC_COUNT
    };

    s32 uniformLocs[LOC_COUNT];
    Shader* shader;
};

DirectionalLight CreateDirectionalLight(glm::vec3 direction, glm::vec3 color, Shader& shader);
void UpdateDirectionalLight(DirectionalLight& light);
