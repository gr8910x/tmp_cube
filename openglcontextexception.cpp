#include "openglcontextexception.h"
#include "openglcontext.h"

using namespace com_defs;

uint OpenGLContextException::counter = 0;

OpenGLContextException::OpenGLContextException() noexcept :
    CommonException (         ),
    m_context       ( nullptr ),
    m_sdlErrorInfo  (         ),
    m_glewErrorInfo (         )
{
    ++ OpenGLContextException::counter;
    fillInfoBytes();
}

OpenGLContextException::OpenGLContextException( const QString &message ) noexcept :
    CommonException ( message ),
    m_context       ( nullptr ),
    m_sdlErrorInfo  (         ),
    m_glewErrorInfo (         )
{
    ++ OpenGLContextException::counter;
    fillInfoBytes();
}

OpenGLContextException::OpenGLContextException( OpenGLContext *context ) noexcept :
    CommonException (         ),
    m_context       ( context ),
    m_sdlErrorInfo  (         ),
    m_glewErrorInfo (         )
{
    ++ OpenGLContextException::counter;
    fillInfoBytes();
}

OpenGLContextException::OpenGLContextException( OpenGLContext *context
                                              , const QString &message ) noexcept :
    CommonException ( message ),
    m_context       ( context ),
    m_sdlErrorInfo  (         ),
    m_glewErrorInfo (         )
{
    ++ OpenGLContextException::counter;
    fillInfoBytes();
}

OpenGLContextException::OpenGLContextException( OpenGLContext *context
                                              , const QString &message
                                              , const QString &sdlErrorInfo
                                              , const QString &glewErrorInfo ) noexcept :
    CommonException ( message       ),
    m_context       ( context       ),
    m_sdlErrorInfo  ( sdlErrorInfo  ),
    m_glewErrorInfo ( glewErrorInfo )
{
    ++ OpenGLContextException::counter;
    fillInfoBytes();
}

OpenGLContextException::OpenGLContextException( const OpenGLContextException &exception ) noexcept :
    CommonException ( exception                 ),
    m_context       ( exception.m_context       ),
    m_sdlErrorInfo  ( exception.m_sdlErrorInfo  ),
    m_glewErrorInfo ( exception.m_glewErrorInfo )
{
}

const OpenGLContextException & OpenGLContextException::operator = (const OpenGLContextException &exception) noexcept
{
    OpenGLContextException::operator = (exception);
    m_context                        = exception.m_context;
    m_sdlErrorInfo                   = exception.m_sdlErrorInfo;
    m_glewErrorInfo                  = exception.m_glewErrorInfo;

    return *this;
}

bool OpenGLContextException::operator == (const OpenGLContextException &exception) const noexcept
{
    bool equal = false;

    if(  OpenGLContextException::operator == (exception)
      && m_context                        == exception.m_context
      && m_sdlErrorInfo                   == exception.m_sdlErrorInfo
      && m_glewErrorInfo                  == exception.m_glewErrorInfo )
    {
        equal = true;
    }

    return equal;
}

bool OpenGLContextException::operator != (const OpenGLContextException &exception) const noexcept
{
    return !(*this == exception);
}

void OpenGLContextException::setContext(OpenGLContext *context) noexcept
{
    m_context = context;
}

void OpenGLContextException::setSDLErrorInfo(const QString &errorInfo) noexcept
{
    m_sdlErrorInfo = errorInfo;
}

void OpenGLContextException::setGLEWErrorInfo(const QString &errorInfo) noexcept
{
    m_glewErrorInfo = errorInfo;
}

const QByteArray & OpenGLContextException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_context )
    {
        uint status = m_context->getStatus();
        infoString += QString("\n OpenGL context name: \t %1").arg(m_context->getName() )
                   +  QString("\n OpenGL context description: %1").arg(m_context->getDescription() );
        if( !m_context->isCreated() )
        {
            infoString += "\n OpenGL context not created.";
        }
        if( (status & OpenGLContextStatus::INVALID_WINDOW_POINTER) == OpenGLContextStatus::INVALID_WINDOW_POINTER )
        {
            infoString += "\n Invalid pointer to application window object.";
        }
        if( (status & OpenGLContextStatus::INVALID_MAKING_CURRENT) == OpenGLContextStatus::INVALID_MAKING_CURRENT )
        {
            infoString += "\n Invalid setting up an OpenGL context for rendering into an SDL OpenGL window while calling SDL_GL_MakeCurrent().";
        }
        if( (status & OpenGLContextStatus::NO_ENGINE_POINTER) == OpenGLContextStatus::NO_ENGINE_POINTER )
        {
            infoString += "\n Engine pointer not set.";
        }
        if( !m_sdlErrorInfo.isEmpty() )
        {
            infoString += QString("\n SDL error info: \n %1").arg(m_sdlErrorInfo.trimmed() );
        }
        if( !m_glewErrorInfo.isEmpty() )
        {
            infoString += QString("\n GLEW error info: \n %1").arg(m_glewErrorInfo.trimmed() );
        }
    }

    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
