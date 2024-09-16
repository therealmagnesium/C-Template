#include "Graphics/Texture.h"

#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>

Texture LoadTexture(const char* path, TextureFormat format)
{
    Texture texture;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    u8* data = stbi_load(path, &texture.width, &texture.height, &texture.channelCount, 0);
    if (!data)
    {
        WARN("Failed to load texture %s!", path);
        stbi_image_free(data);
        return (Texture){.isValid = false};
    }

    u32 glFormat = (format == RGB) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, glFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    texture.isValid = true;

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    INFO("Successfully loaded texture %s!", path);
    return texture;
}

void BindTexture(const Texture& texture, u8 slot)
{
    if (!texture.isValid)
    {
        WARN("Texture at slot %d is not valid!", slot);
        return;
    }

    glBindTexture(GL_TEXTURE_2D, texture.id);
    glActiveTexture(GL_TEXTURE0 + slot);
}
