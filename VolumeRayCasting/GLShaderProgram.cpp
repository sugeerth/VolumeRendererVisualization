#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram()
{
    vertexShader = 0;
    fragmentShader = 0;
    shaderProgram = 0;
}

GLuint GLShaderProgram::createShaderFromFile(const std::string &file, GLenum shaderType)
{
    if(file.empty())
        return 0;

    std::ifstream ifs(file.c_str());
    if(!ifs.is_open())
    {
        qDebug() << "cannot find" << file.c_str();
        return 0;
    }

    ifs.seekg(0, std::ios::end);
    std::string source(ifs.tellg(), 0);
    ifs.seekg(0, std::ios::beg);
    ifs.read(&source.front(), source.size());
    ifs.close();
    //qDebug() << source.c_str();

    qDebug() << "compiling" << file.c_str() << "...";
    GLuint shader = glCreateShader(shaderType);
    if(shader == 0)
        return shader;

    const GLchar *sourcePtr = &source.front();
    glShaderSource(shader, 1, &sourcePtr, NULL);
    glCompileShader(shader);

    int length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    std::string infoLog(length, 0);
    glGetShaderInfoLog(shader, length, NULL, &infoLog.front());
    if(infoLog.size() > 0)
        qDebug() << infoLog.c_str();

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        glDeleteShader(shader);
        shader = 0;
    }

    return shader;
}

GLShaderProgram::~GLShaderProgram()
{
    if(shaderProgram != 0)
        glDeleteProgram(shaderProgram);
    if(vertexShader != 0)
        glDeleteShader(vertexShader);
    if(fragmentShader != 0)
        glDeleteShader(fragmentShader);
}

GLShaderProgram::Ptr GLShaderProgram::create(const std::string &fileVS, const std::string &fileFS)
{
    Ptr shaderPtr(new GLShaderProgram());

    // compile shader
    shaderPtr->vertexShader = createShaderFromFile(fileVS, GL_VERTEX_SHADER);
    shaderPtr->fragmentShader = createShaderFromFile(fileFS, GL_FRAGMENT_SHADER);
    if(shaderPtr->vertexShader == 0 || shaderPtr->fragmentShader == 0)
        return NULL;

    shaderPtr->shaderProgram = glCreateProgram();
    glAttachShader(shaderPtr->shaderProgram, shaderPtr->vertexShader);
    glAttachShader(shaderPtr->shaderProgram, shaderPtr->fragmentShader);
    qDebug() << "linking ...";
    glLinkProgram(shaderPtr->shaderProgram);

    GLint status;
    glGetProgramiv(shaderPtr->shaderProgram, GL_LINK_STATUS, &status);
    if(!status)
        return NULL;

    return shaderPtr;
}

GLuint GLShaderProgram::programID()
{
    return shaderProgram;
}

void GLShaderProgram::setVertexAttribute(const GLchar *name, GLVertexArray::Ptr array, GLArrayBuffer::Ptr buffer, GLint size, GLenum type, GLboolean normalized)
{
    if(buffer->bufferType() == GL_ARRAY_BUFFER)
    {
        GLint index = glGetAttribLocation(shaderProgram, name);
        array->setAttributeArrayBuffer(buffer, index, size, type, normalized);
    }
}

void GLShaderProgram::setUniform(const GLchar *name, float value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform1f(shaderProgram, location, value);
}

void GLShaderProgram::setUniform(const GLchar *name, const Vec2f &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform2f(shaderProgram, location, value.x, value.y);
}

void GLShaderProgram::setUniform(const GLchar *name, const Vec3f &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform3f(shaderProgram, location, value.x, value.y, value.z);
}

void GLShaderProgram::setUniform(const GLchar *name, const Vec4f &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform4f(shaderProgram, location, value.x, value.y, value.z, value.w);
}

void GLShaderProgram::setUniform(const GLchar *name, const Mat3f &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniformMatrix3fv(shaderProgram, location, 1, true, &value.elem[0][0]);
}

void GLShaderProgram::setUniform(const GLchar *name, const Mat4f &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniformMatrix4fv(shaderProgram, location, 1, true, &value.elem[0][0]);
}

void GLShaderProgram::setUniform(const GLchar *name, int value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform1i(shaderProgram, location, value);
}

void GLShaderProgram::setUniform(const GLchar *name, const Vec2i &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform2i(shaderProgram, location, value.x, value.y);
}

void GLShaderProgram::setUniform(const GLchar *name, const Vec3i &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform3i(shaderProgram, location, value.x, value.y, value.z);
}

void GLShaderProgram::setUniform(const GLchar *name, const Vec4i &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform4i(shaderProgram, location, value.x, value.y, value.z, value.w);
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const float *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform1fv(shaderProgram, location, count, value);
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Vec2f *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform2fv(shaderProgram, location, count, reinterpret_cast<const float *>(value));
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Vec3f *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform3fv(shaderProgram, location, count, reinterpret_cast<const float *>(value));
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Vec4f *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform4fv(shaderProgram, location, count, reinterpret_cast<const float *>(value));
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Mat3f *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniformMatrix3fv(shaderProgram, location, count, true, &value->elem[0][0]);
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Mat4f *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniformMatrix4fv(shaderProgram, location, count, true, &value->elem[0][0]);
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const int *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform1iv(shaderProgram, location, count, value);
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Vec2i *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform2iv(shaderProgram, location, count, reinterpret_cast<const int *>(value));
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Vec3i *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform3iv(shaderProgram, location, count, reinterpret_cast<const int *>(value));
}

void GLShaderProgram::setUniformArray(const GLchar *name, int count, const Vec4i *value)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glProgramUniform4iv(shaderProgram, location, count, reinterpret_cast<const int *>(value));
}

void GLShaderProgram::setTexture(const GLchar *name, GLTexture::Ptr texture)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    if(location < 0)
        return;

    SamplerMap::iterator it = samplerMap.find(location);
    GLuint index;
    if(it != samplerMap.end())
        index = it->second;
    else
    {
        index = int(samplerMap.size());
        samplerMap[location] = index;
        glUseProgram(shaderProgram);
        glUniform1i(location, index);
    }

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(texture->type(), texture->textureID());
}

void GLShaderProgram::begin()
{
    glUseProgram(shaderProgram);
}

void GLShaderProgram::end()
{
    glUseProgram(0);
}
