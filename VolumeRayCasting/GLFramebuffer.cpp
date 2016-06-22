#include "GLFramebuffer.h"
#include <iostream>
using namespace std;


GLFramebuffer::GLFramebuffer()
{
    buffer = 0;
    target = GL_FRAMEBUFFER;
    glGenFramebuffers(1, &buffer);
}

GLFramebuffer::~GLFramebuffer()
{
    if(buffer != 0)
        glDeleteFramebuffers(1, &buffer);
}

GLFramebuffer::Ptr GLFramebuffer::create()
{
    Ptr bufferPtr(new GLFramebuffer());
    if(bufferPtr->buffer == 0)
        return NULL;
    else
        return bufferPtr;
}

GLuint GLFramebuffer::bufferID()
{
    return buffer;
}

bool GLFramebuffer::isComplete()
{
    return glCheckFramebufferStatus(target) == GL_FRAMEBUFFER_COMPLETE;
}

void GLFramebuffer::attachTexture(GLenum attachment, GLTexture::Ptr texture, GLint level, GLint layer)
{
    GLenum textureTarget = texture->type();
    GLuint bufferOld;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)&bufferOld);
    glBindFramebuffer(target, buffer);

    switch(textureTarget)
    {
    case GL_TEXTURE_1D:
        glFramebufferTexture1D(target, attachment, textureTarget, texture->textureID(), level);
        break;
    case GL_TEXTURE_2D:
        glFramebufferTexture2D(target, attachment, textureTarget, texture->textureID(), level);
        break;
    case GL_TEXTURE_3D:
        glFramebufferTextureLayer(target, attachment, texture->textureID(), level, layer);
        break;
    }

    glBindFramebuffer(target, bufferOld);
}

void GLFramebuffer::bind()
{
    glBindFramebuffer(target, buffer);
}

void GLFramebuffer::release()
{
    glBindFramebuffer(target, 0);
}
