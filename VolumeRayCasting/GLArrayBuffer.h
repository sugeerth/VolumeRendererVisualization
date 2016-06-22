#ifndef GL_ARRAY_BUFFER_H
#define GL_ARRAY_BUFFER_H

#include "GLConfig.h"

class GLArrayBuffer
{
public:
    typedef std::shared_ptr<GLArrayBuffer> Ptr;

protected:
    GLuint buffer;
    GLenum target;

protected:
    GLArrayBuffer();

public:
    ~GLArrayBuffer();
    static Ptr create(GLenum target);   // GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
    GLuint bufferID();
    GLenum bufferType();
    void update(GLsizeiptr size, const GLvoid *data, GLenum usage);
};

#endif // GLARRAYBUFFER_H
