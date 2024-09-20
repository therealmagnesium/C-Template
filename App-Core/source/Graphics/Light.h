#include "Core/Base.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <glm/glm.hpp>

enum LightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT,
    LIGHT_SPOTLIGHT,
    LIGHT_TYPE_COUNT
};

struct DirectionalLight
{
    glm::vec3 direction;
    glm::vec3 color;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    enum LightUniformLocation
    {
        LOC_TYPE = 0,
        LOC_DIRECTION,
        LOC_COLOR,
        LOC_AMBIENT_INTENSITY,
        LOC_DIFFUSE_INTENSITY,
        LOC_SPECULAR_INTENSITY,
        LOC_COUNT
    };

    s32 uniformLocs[LOC_COUNT];
    Shader* shader;
};

struct Spotlight
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;

    float cutoff;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    enum LightUniformLocation
    {
        LOC_TYPE = 0,
        LOC_POSITION,
        LOC_DIRECTION,
        LOC_COLOR,
        LOC_CUTOFF,
        LOC_AMBIENT_INTENSITY,
        LOC_DIFFUSE_INTENSITY,
        LOC_SPECULAR_INTENSITY,
        LOC_COUNT
    };

    s32 uniformLocs[LOC_COUNT];
    Shader* shader;
};

DirectionalLight CreateDirectionalLight(glm::vec3 direction, glm::vec3 color, Shader& shader);
Spotlight CreateSpotlight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, Shader& shader);
void UpdateDirectionalLight(DirectionalLight& light);
void UpdateSpotlight(Spotlight& light);
