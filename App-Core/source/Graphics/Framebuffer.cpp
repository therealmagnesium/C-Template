#include "Graphics/Framebuffer.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>

Framebuffer CreateFramebuffer(const FramebufferSpecification& spec)
{
    Framebuffer framebuffer;
    framebuffer.specification = spec;

    glCreateFramebuffers(1, &framebuffer.id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.id);

    glGenTextures(1, &framebuffer.colorAttachment);
    glBindTexture(GL_TEXTURE_2D, framebuffer.colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer.colorAttachment, 0);

    glGenRenderbuffers(1, &framebuffer.renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, framebuffer.renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, spec.width, spec.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebuffer.renderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        ERROR("Failed to create framebuffer!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return framebuffer;
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, id); }

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
