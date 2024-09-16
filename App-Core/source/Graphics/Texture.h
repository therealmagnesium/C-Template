#pragma once
#include "Core/Base.h"

enum TextureFormat
{
    RGB = 0,
    RGBA,
};

struct Texture
{
    u32 id;
    b8 isValid;
    s32 width;
    s32 height;
    s32 channelCount;
};

Texture LoadTexture(const char* path, TextureFormat format);
void BindTexture(const Texture& texture, u8 slot);
