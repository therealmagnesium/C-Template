#pragma once
#include "Core/Base.h"

struct FramebufferSpecification
{
    u32 width;
    u32 height;
    u32 numSamples = 1;
    b8 isSwapChainTarget = false;
};

struct Framebuffer
{
    u32 id;
    u32 colorAttachment;
    u32 renderBuffer;
    FramebufferSpecification specification;

    void Bind();
    void Unbind();
};

Framebuffer CreateFramebuffer(const FramebufferSpecification& spec);
