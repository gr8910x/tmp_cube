#ifndef IOPENGLCONTEXT_H
#define IOPENGLCONTEXT_H

//! Interface for OpenGL context implementation.

class Scene;

class IOpenGLContext
{
public:
    virtual void create() noexcept(false) = 0;                           //! Creates OpenGL context for use with an SDL OpenGL window and makes it current, initializes GLEW library.
    virtual void draw() noexcept(false) = 0;                             //! Draws scene into OpenGL context.
    virtual void destroy() = 0;                                          //! Destroys OpenGL context.
    virtual void makeCurrent() noexcept(false) = 0;                      //! Sets up OpenGL context for rendering into an SDL OpenGL window.

    virtual ~IOpenGLContext() {}

};

#endif // IOPENGLCONTEXT_H
