#ifndef GL_FRAMEBUFFER_H
#define GL_FRAMEBUFFER_H

#include "GLConfig.h"
#include "GLTexture.h"

class GLFramebuffer
{
public:
    typedef std::shared_ptr<GLFramebuffer> Ptr;

protected:
    GLuint buffer;
    GLenum target;

protected:
    GLFramebuffer();

public:
    ~GLFramebuffer();
    static Ptr create();
    GLuint bufferID();
    bool isComplete();
    void attachTexture(GLenum attachment, GLTexture::Ptr texture, GLint level = 0, GLint layer = 0);
    void bind();
    void release();
};

#endif // GLFRAMEBUFFER_H
