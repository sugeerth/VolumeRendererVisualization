#include "GLTexture.h"
#include <fstream>
#include "GLWidget.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

GLTexture::GLTexture()
{
    target = GL_TEXTURE_2D;
    texture = 0;
    glGenTextures(1, &texture);
}

GLTexture::~GLTexture()
{
    if(texture != 0)
        glDeleteTextures(1, &texture);
}

GLTexture::Ptr GLTexture::create()
{
    Ptr texturePtr(new GLTexture());
    if(texturePtr->texture == 0)
        return NULL;
    else
        return texturePtr;
}

GLenum GLTexture::type()
{
    return target;
}

GLuint GLTexture::textureID()
{
    return texture;
}

void GLTexture::generateMipmap()
{
    glBindTexture(target, texture);
    glGenerateMipmap(target);
    glBindTexture(target, 0);
}


void GLTexture::setTextureParameter(GLenum pname, GLfloat param)
{
    glBindTexture(target, texture);
    glTexParameterf(target, pname, param);
    glBindTexture(target, 0);
}

void GLTexture::setTextureParameter(GLenum pname, GLint param)
{
    glBindTexture(target, texture);
    glTexParameteri(target, pname, param);
    glBindTexture(target, 0);
}

void GLTexture::updateTexImage2D(GLint internalFormat, const Vec2i &size, GLenum format, GLenum type, const GLvoid *data)
{
    target = GL_TEXTURE_2D;
    GLuint textureOld;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&textureOld);
    glBindTexture(target, texture);
    glTexImage2D(target, 0, internalFormat, size.x, size.y, 0, format, type, data);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(target, textureOld);
}

void GLTexture::updateTexSubImage2D(GLint xoffset, GLint yoffset, const Vec2i &size, GLenum format, GLenum type, const GLvoid *data)
{
    if(target != GL_TEXTURE_2D)
        return;

    GLuint textureOld;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&textureOld);
    glBindTexture(target, texture);
    glTexSubImage2D(target, 0, xoffset, yoffset, size.x, size.y, format, type, data);
    glBindTexture(target, textureOld);
}

void GLTexture::updateTexImage3D(GLint internalFormat, const Vec3i &size, GLenum format, GLenum type, const GLvoid *data)
{
    target = GL_TEXTURE_3D;
    GLuint textureOld;
    glGetIntegerv(GL_TEXTURE_BINDING_3D, (GLint *)&textureOld);
    glBindTexture(target, texture);
    glTexImage3D(target, 0, internalFormat, size.x, size.y, size.z, 0, format, type, data);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(target, textureOld);
}

void GLTexture::updateTexSubImage3D(const Vec3i &offset, const Vec3i &size, GLenum format, GLenum type, const GLvoid *data)
{
    if(target != GL_TEXTURE_3D)
        return;

    GLuint textureOld;
    glGetIntegerv(GL_TEXTURE_BINDING_3D, (GLint *)&textureOld);
    glBindTexture(target, texture);
    glTexSubImage3D(target, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, format, type, data);
    glBindTexture(target, textureOld);
}

void GLTexture::updateTexImageCube(GLint internalFormat, const Vec2i &size, GLenum format, GLenum type, const GLvoid **data)
{
    //
    target = GL_TEXTURE_CUBE_MAP;
    GLuint textureOld;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&textureOld);
    glBindTexture(target, texture);
    for(int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, size.x, size.y, 0, format, type, data[i]);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(target);
    glBindTexture(target, textureOld);
}
