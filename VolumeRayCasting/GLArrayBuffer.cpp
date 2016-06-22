#include "GLArrayBuffer.h"

GLArrayBuffer::GLArrayBuffer()
{
    buffer = 0;
    target = GL_ARRAY_BUFFER;
    glGenBuffers(1, &buffer);
}

GLArrayBuffer::~GLArrayBuffer()
{
    if(buffer != 0)
        glDeleteBuffers(1, &buffer);
}

GLArrayBuffer::Ptr GLArrayBuffer::create(GLenum target)    // GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
{
    Ptr bufferPtr(new GLArrayBuffer());
    if(bufferPtr->buffer == 0)
        return NULL;

    bufferPtr->target = target;
    return bufferPtr;
}

GLuint GLArrayBuffer::bufferID()
{
    return buffer;
}

GLenum GLArrayBuffer::bufferType()
{
    return target;
}

void GLArrayBuffer::update(GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    GLuint bufferOld = 0;
    switch(target)
    {
    case GL_ARRAY_BUFFER:
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint *)&bufferOld);
        break;
    case GL_ELEMENT_ARRAY_BUFFER:
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint *)&bufferOld);
        break;
    }

    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, bufferOld);
}
