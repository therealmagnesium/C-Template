#include "Graphics/Light.h"
#include "Graphics/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

DirectionalLight CreateDirectionalLight(glm::vec3 direction, glm::vec3 color, Shader& shader)
{
    DirectionalLight light;
    light.direction = direction;
    light.color = color;
    light.ambientIntensity = 0.6f;
    light.diffuseIntensity = 1.2f;
    light.specularIntensity = 0.5f;

    if (shader.id == 0)
        shader = Renderer.state.defaultShader;

    light.uniformLocs[DirectionalLight::LOC_TYPE] = GetUniformLocation(shader, "light.type");
    light.uniformLocs[DirectionalLight::LOC_DIRECTION] = GetUniformLocation(shader, "light.direction");
    light.uniformLocs[DirectionalLight::LOC_COLOR] = GetUniformLocation(shader, "light.color");
    light.uniformLocs[DirectionalLight::LOC_AMBIENT_INTENSITY] = GetUniformLocation(shader, "light.ambientIntensity");
    light.uniformLocs[DirectionalLight::LOC_DIFFUSE_INTENSITY] = GetUniformLocation(shader, "light.diffuseIntensity");
    light.uniformLocs[DirectionalLight::LOC_SPECULAR_INTENSITY] = GetUniformLocation(shader, "light.specularIntensity");

    light.shader = &shader;
    return light;
}

void UpdateDirectionalLight(DirectionalLight& light)
{
    if (light.shader->id == 0 || !light.shader)
        light.shader = &Renderer.state.defaultShader;

    light.shader->Bind();
    light.shader->SetInt(light.uniformLocs[DirectionalLight::LOC_TYPE], LIGHT_DIRECTIONAL);
    light.shader->SetVec3(light.uniformLocs[DirectionalLight::LOC_DIRECTION], glm::value_ptr(light.direction));
    light.shader->SetVec3(light.uniformLocs[DirectionalLight::LOC_COLOR], glm::value_ptr(light.color));
    light.shader->SetFloat(light.uniformLocs[DirectionalLight::LOC_AMBIENT_INTENSITY], light.ambientIntensity);
    light.shader->SetFloat(light.uniformLocs[DirectionalLight::LOC_DIFFUSE_INTENSITY], light.diffuseIntensity);
    light.shader->SetFloat(light.uniformLocs[DirectionalLight::LOC_SPECULAR_INTENSITY], light.specularIntensity);
    light.shader->Unbind();
}

Spotlight CreateSpotlight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, Shader& shader)
{
    Spotlight light;
    light.position = position;
    light.direction = direction;
    light.color = color;
    light.cutoff = cos(glm::radians(12.f));
    light.ambientIntensity = 0.6f;
    light.diffuseIntensity = 1.2f;
    light.specularIntensity = 0.5f;

    if (shader.id == 0)
        shader = Renderer.state.defaultShader;

    light.uniformLocs[Spotlight::LOC_TYPE] = GetUniformLocation(shader, "light.type");
    light.uniformLocs[Spotlight::LOC_POSITION] = GetUniformLocation(shader, "light.position");
    light.uniformLocs[Spotlight::LOC_DIRECTION] = GetUniformLocation(shader, "light.direction");
    light.uniformLocs[Spotlight::LOC_COLOR] = GetUniformLocation(shader, "light.color");
    light.uniformLocs[Spotlight::LOC_CUTOFF] = GetUniformLocation(shader, "light.cutoff");
    light.uniformLocs[Spotlight::LOC_AMBIENT_INTENSITY] = GetUniformLocation(shader, "light.ambientIntensity");
    light.uniformLocs[Spotlight::LOC_DIFFUSE_INTENSITY] = GetUniformLocation(shader, "light.diffuseIntensity");
    light.uniformLocs[Spotlight::LOC_SPECULAR_INTENSITY] = GetUniformLocation(shader, "light.specularIntensity");

    light.shader = &shader;
    return light;
}

void UpdateSpotlight(Spotlight& light)
{
    if (light.shader->id == 0 || !light.shader)
        light.shader = &Renderer.state.defaultShader;

    light.shader->Bind();
    light.shader->SetInt(light.uniformLocs[Spotlight::LOC_TYPE], LIGHT_SPOTLIGHT);
    light.shader->SetVec3(light.uniformLocs[Spotlight::LOC_POSITION], glm::value_ptr(light.position));
    light.shader->SetVec3(light.uniformLocs[Spotlight::LOC_DIRECTION], glm::value_ptr(light.direction));
    light.shader->SetVec3(light.uniformLocs[Spotlight::LOC_COLOR], glm::value_ptr(light.color));
    light.shader->SetFloat(light.uniformLocs[Spotlight::LOC_CUTOFF], light.cutoff);
    light.shader->SetFloat(light.uniformLocs[Spotlight::LOC_AMBIENT_INTENSITY], light.ambientIntensity);
    light.shader->SetFloat(light.uniformLocs[Spotlight::LOC_DIFFUSE_INTENSITY], light.diffuseIntensity);
    light.shader->SetFloat(light.uniformLocs[Spotlight::LOC_SPECULAR_INTENSITY], light.specularIntensity);
    light.shader->Unbind();
}
