#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec2 fragTexCoords;
in vec3 fragNormal;

const int LIGHT_DIRECTIONAL = 0;
const int LIGHT_POINT = 1;
const int LIGHT_SPOTLIGHT = 2;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseMap;
    sampler2D specularMap;
};

struct Light
{
    int type;

    vec3 position;
    vec3 direction;
    vec3 color;

    float cutoff;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

uniform Material material;
uniform Light light;

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

vec3 CalculateAmbient(Material m, Light l)
{
    vec3 a = m.ambient * l.ambientIntensity;
    return a;
}

vec3 CalculateDiffuse(Material m, Light l)
{
    vec3 n = normalize(fragNormal);
    vec3 ld = normalize(-l.direction);
    vec3 dt = texture(m.diffuseMap, fragTexCoords).xyz;
    float df = max(dot(n, ld), 0.f);
    vec3 diff = vec3(0.f);

    if (any(greaterThan(dt, vec3(0.f))))
        diff = df * m.diffuse * dt * l.diffuseIntensity * l.color;
    else
        diff = df * m.diffuse * l.diffuseIntensity * l.color;

    return diff;
}

vec3 CalculateSpecular(Material m, Light l)
{
    vec3 n = normalize(fragNormal);
    vec3 ld = normalize(-l.direction);
    vec3 vd = normalize(viewPosition - fragPosition);
    vec3 rd = reflect(-ld, n);
    
    float sf = pow(max(dot(vd, rd), 0.f), 8.f);
    vec3 s = l.specularIntensity * l.color * sf * m.specular;
    return s;
}

void main()
{
    vec3 objectColor = GetObjectColor(material);
    vec3 ambient = CalculateAmbient(material, light);
    vec3 diffuse = CalculateDiffuse(material, light);
    vec3 specular = CalculateSpecular(material, light);

    vec3 result = vec3(0.f); 
    switch (light.type)
    {
        case LIGHT_DIRECTIONAL:
        {
            result = objectColor * ambient + diffuse + specular;
            break;
        }

        case LIGHT_POINT:
        {

            break;
        }

        case LIGHT_SPOTLIGHT:
        {
            vec3 ld = normalize(light.position - fragPosition);
            vec3 sd = normalize(-light.direction);
            float theta = dot(ld, sd);

            if (theta > light.cutoff)
                result = objectColor * ambient + diffuse + specular;
            else
                result = objectColor * ambient;
            break;
        }

        default:
            break;
    }

    finalColor = vec4(result, 1.f);
}
