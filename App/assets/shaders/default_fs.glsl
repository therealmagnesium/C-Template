#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec2 fragTexCoords;
in vec3 fragNormal;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseMap;
    sampler2D specularMap;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 color;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

uniform Material material;
uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;

vec3 GetObjectColor(Material m)
{
    vec3 c = vec3(0.f);
    vec3 dt = texture(material.diffuseMap, fragTexCoords).xyz;

    if (any(greaterThan(dt, vec3(0.f))))
        c = dt * m.diffuse;
    else
        c = m.diffuse;

    return c;
}

vec3 CalculateAmbient(Material m, DirectionalLight d)
{
    vec3 a = m.ambient * d.ambientIntensity;
    return a;
}

vec3 CalculateDiffuse(Material m, DirectionalLight d)
{
    vec3 n = normalize(fragNormal);
    vec3 ld = normalize(-d.direction);
    vec3 dt = texture(m.diffuseMap, fragTexCoords).xyz;
    float df = max(dot(n, ld), 0.f);
    vec3 diff = vec3(0.f);

    if (any(greaterThan(dt, vec3(0.f))))
        diff = df * m.diffuse * dt * d.diffuseIntensity * d.color;
    else
        diff = df * m.diffuse * d.diffuseIntensity * d.color;

    return diff;
}

vec3 CalculateSpecular(Material m, DirectionalLight d)
{
    vec3 n = normalize(fragNormal);
    vec3 ld = normalize(-d.direction);
    vec3 vd = normalize(viewPosition - fragPosition);
    vec3 rd = reflect(-ld, n);
    
    float sf = pow(max(dot(vd, rd), 0.f), 32.f);
    vec3 s = d.specularIntensity * d.color * sf * m.specular;
    return s;
}

void main()
{
    vec3 ambient = CalculateAmbient(material, directionalLight);
    vec3 diffuse = CalculateDiffuse(material, directionalLight);
    vec3 specular = CalculateSpecular(material, directionalLight);

    vec3 result = ambient + diffuse + specular; 

    vec3 objectColor = GetObjectColor(material);
    finalColor = vec4(objectColor, 1.f) * vec4(result, 1.f);
}
