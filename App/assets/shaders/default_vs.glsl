#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 fragPosition;
out vec2 fragTexCoords;
out vec3 fragNormal;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matNormal;

void main()
{
    fragPosition = position;
    fragTexCoords = texCoord;
    fragNormal = mat3(matNormal) * normal;
    gl_Position = matProjection * matView * matModel * vec4(position, 1.f);
}
