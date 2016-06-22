#include "GLVertexArray.h"

GLVertexArray::GLVertexArray()
{
    array = 0;
    glGenVertexArrays(1, &array);
}

GLVertexArray::~GLVertexArray()
{
    if(array != 0)
        glDeleteVertexArrays(1, &array);
}

GLVertexArray::Ptr GLVertexArray::create()
{
    Ptr arrayPtr(new GLVertexArray());
    if(arrayPtr->array == 0)
        return NULL;
    else
        return arrayPtr;
}


void GLVertexArray::setAttributeArrayBuffer(GLArrayBuffer::Ptr buffer, GLuint index, GLint size, GLenum type, GLboolean normalized)
{
    if(buffer->bufferType() == GL_ARRAY_BUFFER)
    {
        glBindVertexArray(array);
        glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID());
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, 0, NULL);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void GLVertexArray::setElementArrayBuffer(GLArrayBuffer::Ptr buffer)
{
    if(buffer->bufferType() == GL_ELEMENT_ARRAY_BUFFER)
    {
        glBindVertexArray(array);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferID());
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void GLVertexArray::drawArrays(GLenum mode, GLsizei count)
{
    glBindVertexArray(array);
    glDrawArrays(mode, 0, count);
    glBindVertexArray(0);
}

void GLVertexArray::drawElements(GLenum mode, GLsizei count, GLenum type)
{
    glBindVertexArray(array);
    glDrawElements(mode, count, type, NULL);
    glBindVertexArray(0);
}
