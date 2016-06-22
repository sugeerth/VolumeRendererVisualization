#ifndef GL_SHADER_PROGRAM_H
#define GL_SHADER_PROGRAM_H

#include "GLConfig.h"
#include "GLVertexArray.h"
#include "GLTexture.h"

class GLShaderProgram
{
public:
    typedef std::shared_ptr<GLShaderProgram> Ptr;
    typedef std::map<GLint, GLuint> SamplerMap;

protected:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    SamplerMap samplerMap;

protected:
    GLShaderProgram();
    static GLuint createShaderFromFile(const std::string &file, GLenum shaderType);

public:
    ~GLShaderProgram();
    static Ptr create(const std::string &fileVS, const std::string &fileFS);
    GLuint programID();
    void setVertexAttribute(const GLchar *name, GLVertexArray::Ptr array, GLArrayBuffer::Ptr buffer, GLint size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE);
    void setUniform(const GLchar *name, float value);
    void setUniform(const GLchar *name, const Vec2f &value);
    void setUniform(const GLchar *name, const Vec3f &value);
    void setUniform(const GLchar *name, const Vec4f &value);
    void setUniform(const GLchar *name, const Mat3f &value);
    void setUniform(const GLchar *name, const Mat4f &value);
    void setUniform(const GLchar *name, int value);
    void setUniform(const GLchar *name, const Vec2i &value);
    void setUniform(const GLchar *name, const Vec3i &value);
    void setUniform(const GLchar *name, const Vec4i &value);
    void setUniformArray(const GLchar *name, int count, const float *value);
    void setUniformArray(const GLchar *name, int count, const Vec2f *value);
    void setUniformArray(const GLchar *name, int count, const Vec3f *value);
    void setUniformArray(const GLchar *name, int count, const Vec4f *value);
    void setUniformArray(const GLchar *name, int count, const Mat3f *value);
    void setUniformArray(const GLchar *name, int count, const Mat4f *value);
    void setUniformArray(const GLchar *name, int count, const int *value);
    void setUniformArray(const GLchar *name, int count, const Vec2i *value);
    void setUniformArray(const GLchar *name, int count, const Vec3i *value);
    void setUniformArray(const GLchar *name, int count, const Vec4i *value);
    void setTexture(const GLchar *name, GLTexture::Ptr texture);
    void begin();
    void end();
};

#endif // GLSHADERPROGRAM_H
