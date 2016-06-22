#ifndef GL_VERTEX_ARRAY_H
#define GL_VERTEX_ARRAY_H

#include "GLConfig.h"
#include "GLArrayBuffer.h"

class GLVertexArray
{
public:
    typedef std::shared_ptr<GLVertexArray> Ptr;

protected:
    GLuint array;

protected:
    GLVertexArray();

public:
    ~GLVertexArray();
    static Ptr create();
    // deprecated: for fixed function pipeline
    //void setVertexArrayBuffer(GLArrayBuffer::Ptr buffer, GLint size, GLenum type = GL_FLOAT);
    void setAttributeArrayBuffer(GLArrayBuffer::Ptr buffer, GLuint index, GLint size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE);
    void setElementArrayBuffer(GLArrayBuffer::Ptr buffer);
    void drawArrays(GLenum mode, GLsizei count);
    void drawElements(GLenum mode, GLsizei count, GLenum type);
};

#endif // GLVERTEXARRAY_H
