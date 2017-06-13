#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "commonincludings.h"
#include "iopenglcontext.h"

class Engine;
class AppWindow;

//! Implements OpenGL context.
class OpenGLContext : public IOpenGLContext
{
public:
    OpenGLContext();                                                    //! Default constructor.
    OpenGLContext( const QVector4D          &clearColor );              //! Parameterized constructor.
    OpenGLContext( const QVector4D          &clearColor                 //! Parameterized constructor.
                 , GLfloat                   clearDepth
                 );
    OpenGLContext( GLfloat                   clearRed                   //! Parameterized constructor.
                 , GLfloat                   clearGreen
                 , GLfloat                   clearBlue
                 , GLfloat                   clearAlpha
                 );
    OpenGLContext( GLfloat                   clearRed                   //! Parameterized constructor.
                 , GLfloat                   clearGreen
                 , GLfloat                   clearBlue
                 , GLfloat                   clearAlpha
                 , GLfloat                   clearDepth
                 );
    OpenGLContext( Engine                   *engine );                  //! Parameterized constructor.
    OpenGLContext( Engine                   *engine                     //! Parameterized constructor.
                 , std::weak_ptr<AppWindow>  window
                 );
    OpenGLContext( const QVector4D          &clearColor                 //! Parameterized constructor.
                 , GLfloat                   clearDepth
                 , Engine                   *engine
                 , std::weak_ptr<AppWindow>  window
                 , const QString            &description = "Empty description"
                 );
    OpenGLContext( GLfloat                   clearRed                   //! Parameterized constructor.
                 , GLfloat                   clearGreen
                 , GLfloat                   clearBlue
                 , GLfloat                   clearAlpha
                 , GLfloat                   clearDepth
                 , Engine                   *engine
                 , std::weak_ptr<AppWindow>  window
                 , const QString            &description = "Empty description"
                 );

    virtual ~OpenGLContext();

    virtual void create() noexcept(false) override;                     //! Creates OpenGL context for use with an SDL OpenGL window and makes it current, initializes GLEW library.
    virtual void draw() noexcept(false) override;                       //! Draws scene into OpenGL context.
    virtual void destroy() override;                                    //! Destroys OpenGL context.
    virtual void makeCurrent() noexcept(false) override;                //! Sets up OpenGL context for rendering into an SDL OpenGL window.

    const OpenGLContext & operator = (const OpenGLContext &context);    //! Operator " =  ".
    bool  operator == (const OpenGLContext &context) const;             //! Operator " == ".
    bool  operator != (const OpenGLContext &context) const;             //! Operator " != ".

public:
    const QVector4D & getClearColor() const { return m_clearColor; }    //! Returns OpenGL buffer clear color in RGBA format.
    QVector4D & getClearColor() { return m_clearColor; }                //! Returns OpenGL buffer clear color in RGBA format, overloaded function.
    GLfloat getClearRed() const { return m_clearColor.x(); }            //! Returns OpenGL buffer clear red color.
    GLfloat getClearGreen() const { return m_clearColor.y(); }          //! Returns OpenGL buffer clear green color.
    GLfloat getClearBlue() const { return m_clearColor.z(); }           //! Returns OpenGL buffer clear blue color.
    GLfloat getClearAlpha() const { return m_clearColor.w(); }          //! Returns OpenGL buffer clear alpha value.
    void  setClearColor(const QVector4D &clearColor);                   //! Sets OpenGL buffer clear color in RGBA format.
    void  setClearRed(GLfloat red);                                     //! Sets OpenGL buffer clear red color.
    void  setClearGreen(GLfloat green);                                 //! Sets OpenGL buffer clear green color.
    void  setClearBlue(GLfloat blue);                                   //! Sets OpenGL buffer clear blue color.
    void  setClearAlpha(GLfloat alpha);                                 //! Sets OpenGL buffer clear alpha value.

    GLfloat getClearDepth() const { return m_clearDepth; }              //! Returns OpenGL buffer clear depth value.
    void  setClearDepth(GLfloat clearDepth);                            //! Sets OpenGL buffer clear depth value.

    const Engine * getEngine() const { return m_engine; }               //! Returns pointer to engine object.
    Engine * getEngine() { return m_engine; }                           //! Returns pointer to engine object, overloaded function.
    void setEngine(Engine *engine);                                     //! Sets pointer to engine object.

    std::weak_ptr<AppWindow> getWindow() { return m_window; }           //! Returns pointer to application window object.
    void setWindow(std::weak_ptr<AppWindow> window);                    //! Sets pointer to application window object.

    const SDL_GLContext & getSDLGLContext() const { return m_sdlGLContext; }//! Returns SDL OpenGL context.
    SDL_GLContext & getSDLGLContext() { return m_sdlGLContext; }            //! Returns SDL OpenGL context, overloaded function.

    GLuint getName() const { return m_name; }                           //! Returns autogenerated name of OpenGL context.

    const QString & getDescription() const { return m_description; }    //! Returns OpenGL context description.
    void  setDescription(const QString &description);                   //! Sets OpenGL context description.

    uint getStatus() const { return m_status; }                         //! Returns OpenGL context object status bitmask.

    bool isCreated() const;                                             //! Returns true if OpenGL context was created.

public:
    static GLuint getCounter() { return counter; }                      //! Returns number of created OpenGL context objects.

    static std::shared_ptr<OpenGLContext> createObject();               //! Creates new OpenGL context and returns pointer to it.

protected:
    OpenGLContext( const OpenGLContext &context );                      //! Copying constructor.

    void setStatus(uint status) { m_status = status; }                  //! Sets OpenGL context object status bitmask.

private:
    static GLuint counter;          //! Counter of created OpenGL context objects.

private:
    QVector4D     m_clearColor;     //! OpenGL buffer clear color in RGBA format, { 0.0f, 0.0f, 0.0f, 0.0f } by default.
    GLfloat       m_clearDepth;     //! OpenGL buffer clear depth value, 1.0 by default.

    Engine *                  m_engine; //! A pointer to engine object.
    std::weak_ptr<AppWindow>  m_window; //! A pointer to application window object.

    SDL_GLContext m_sdlGLContext;   //! SDL OpenGL context.

    GLuint        m_name;           //! Autogenerated name of OpenGL context.

    QString       m_description;    //! OpenGL context description.

    uint          m_status;         //! OpenGL context object status bitmask.

};

#endif // OPENGLCONTEXT_H
