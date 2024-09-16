#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec2 fragTexCoords;

struct Material
{
    vec4 diffuse;
    sampler2D diffuseMap;
};

uniform Material material;

void main()
{
    vec3 texel = texture(material.diffuseMap, fragTexCoords).xyz;
    vec3 result = vec3(0.f);
    
    if (any(greaterThan(texel, vec3(0.f))))
        result += texel * material.diffuse.xyz;
    else
        result += material.diffuse.xyz;

    finalColor = vec4(result, 1.f);
}
