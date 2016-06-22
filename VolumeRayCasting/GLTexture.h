#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include <fstream>
#include <iostream>
#include "GLConfig.h"

class GLTexture
{
public:
    typedef std::shared_ptr<GLTexture> Ptr;

protected:
    GLenum target;
    GLuint texture;

protected:
    GLTexture();

public:
    ~GLTexture();
    static Ptr create();
    GLenum type();
    GLuint textureID();
    void generateMipmap();
    void setTextureParameter(GLenum pname, GLfloat param);
    void setTextureParameter(GLenum pname, GLint param);
    void updateTexImage2D(GLint internalFormat, const Vec2i &size, GLenum format, GLenum type, const GLvoid *data);
    void updatePreTexImage2D(GLint internalFormat, const Vec2i &size, GLenum format, GLenum type, const GLvoid *data);
    void updateTexSubImage2D(GLint xoffset, GLint yoffset, const Vec2i &size, GLenum format, GLenum type, const GLvoid *data);
    void updateTexImage3D(GLint internalFormat, const Vec3i &size, GLenum format, GLenum type, const GLvoid *data);
    GLuint initTFF1DTex(const char* filename);
    void updateTexSubImage3D(const Vec3i &offset, const Vec3i &size, GLenum format, GLenum type, const GLvoid *data);
    void updateTexImageCube(GLint internalFormat, const Vec2i &size, GLenum format, GLenum type, const GLvoid **data);
};

#endif // GLTEXTURE_H
