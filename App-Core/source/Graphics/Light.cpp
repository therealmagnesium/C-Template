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
    light.diffuseIntensity = 0.8f;
    light.specularIntensity = 0.5f;

    if (shader.id == 0)
        shader = Renderer.state.defaultShader;

    light.uniformLocs[DirectionalLight::LOC_DIRECTION] = GetUniformLocation(shader, "directionalLight.direction");
    light.uniformLocs[DirectionalLight::LOC_COLOR] = GetUniformLocation(shader, "directionalLight.color");
    light.uniformLocs[DirectionalLight::LOC_AMBIENT_INTENSITY] =
        GetUniformLocation(shader, "directionalLight.ambientIntensity");
    light.uniformLocs[DirectionalLight::LOC_DIFFUSE_INTENSITY] =
        GetUniformLocation(shader, "directionalLight.diffuseIntensity");
    light.uniformLocs[DirectionalLight::LOC_SPECULAR_INTENSITY] =
        GetUniformLocation(shader, "directionalLight.specularIntensity");

    light.shader = &shader;
    return light;
}

void UpdateDirectionalLight(DirectionalLight& light)
{
    if (light.shader->id == 0 || !light.shader)
        light.shader = &Renderer.state.defaultShader;

    light.shader->Bind();
    light.shader->SetVec3(light.uniformLocs[DirectionalLight::LOC_DIRECTION], glm::value_ptr(light.direction));
    light.shader->SetVec3(light.uniformLocs[DirectionalLight::LOC_COLOR], glm::value_ptr(light.color));
    light.shader->SetFloat(light.uniformLocs[DirectionalLight::LOC_AMBIENT_INTENSITY], light.ambientIntensity);
    light.shader->SetFloat(light.uniformLocs[DirectionalLight::LOC_DIFFUSE_INTENSITY], light.diffuseIntensity);
    light.shader->SetFloat(light.uniformLocs[DirectionalLight::LOC_SPECULAR_INTENSITY], light.specularIntensity);
    light.shader->Unbind();
}
