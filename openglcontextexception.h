#ifndef OPENGLCONTEXTEXCEPTION_H
#define OPENGLCONTEXTEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class OpenGLContext;

class OpenGLContextException : public CommonException
{
public:
    OpenGLContextException() noexcept;                           //! Default constructor.
    OpenGLContextException( const QString &message ) noexcept;   //! Parameterized constructor.
    OpenGLContextException( OpenGLContext *context ) noexcept;   //! Parameterized constructor.
    OpenGLContextException( OpenGLContext *context               //! Parameterized constructor.
                          , const QString &message ) noexcept;
    OpenGLContextException( OpenGLContext *context               //! Parameterized constructor.
                          , const QString &message
                          , const QString &sdlErrorInfo
                          , const QString &glewErrorInfo = "" ) noexcept;

    OpenGLContextException( const OpenGLContextException &exception) noexcept;//! Copying constructor.

    virtual ~OpenGLContextException() {}

    const OpenGLContextException & operator = (const OpenGLContextException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const OpenGLContextException &exception) const noexcept;                  //! Operator " == ".
    bool  operator != (const OpenGLContextException &exception) const noexcept;                  //! Operator " == ".

public:
    const OpenGLContext * getContext() const noexcept { return m_context; }//! Returns pointer to OpenGL context object where exception occured.
    OpenGLContext * getContext() noexcept { return m_context; }            //! Returns pointer to OpenGL context object where exception occured, overloaded function.
    void setContext(OpenGLContext *context) noexcept;                      //! Sets pointer to OpenGL context object where exception occured.

    const QString & getSDLErrorInfo() const noexcept { return m_sdlErrorInfo; }//! Returns SDL OpenGL context error info.
    void setSDLErrorInfo(const QString &errorInfo) noexcept;                   //! Sets SDL OpenGL context error info.

    const QString & getGLEWErrorInfo() const noexcept { return m_glewErrorInfo; }//! Returns GLEW error info string.
    void setGLEWErrorInfo(const QString &errorInfo) noexcept;                    //! Sets GLEW error info string.

public:
    static uint getCounter() { return counter; }                 //! Returns number of created OpenGL context exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;//! Fills info bytes array with bytes and returns it.

private:
    static uint counter;             //! Counter of created OpenGL context exception objects.

private:
    OpenGLContext *   m_context;     //! A pointer to OpenGL context object where exception occured.

    QString           m_sdlErrorInfo;//! SDL OpenGL context error info.
    QString           m_glewErrorInfo;//! GLEW error info string.
};

#endif // OPENGLCONTEXTEXCEPTION_H
