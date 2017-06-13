#include "appwindowexception.h"
#include "appwindow.h"

using namespace com_defs;

uint AppWindowException::counter = 0;

AppWindowException::AppWindowException() noexcept :
    CommonException (         ),
    m_window        ( nullptr ),
    m_sdlErrorInfo  (         )
{
    ++ AppWindowException::counter;
    fillInfoBytes();
}

AppWindowException::AppWindowException( const QString &message ) noexcept :
    CommonException ( message ),
    m_window        ( nullptr ),
    m_sdlErrorInfo  (         )
{
    ++ AppWindowException::counter;
    fillInfoBytes();
}

AppWindowException::AppWindowException( AppWindow *window ) noexcept :
    CommonException (         ),
    m_window        ( window  ),
    m_sdlErrorInfo  (         )
{
    ++ AppWindowException::counter;
    fillInfoBytes();
}

AppWindowException::AppWindowException( AppWindow     *window
                                      , const QString &message ) noexcept :
    CommonException ( message ),
    m_window        ( window  ),
    m_sdlErrorInfo  (         )
{
    ++ AppWindowException::counter;
    fillInfoBytes();
}

AppWindowException::AppWindowException( AppWindow     *window
                                      , const QString &message
                                      , const QString &sdlErrorInfo ) noexcept :
    CommonException ( message      ),
    m_window        ( window       ),
    m_sdlErrorInfo  ( sdlErrorInfo )
{
    ++ AppWindowException::counter;
    fillInfoBytes();
}

AppWindowException::AppWindowException( const AppWindowException &exception ) noexcept :
    CommonException ( exception                ),
    m_window        ( exception.m_window       ),
    m_sdlErrorInfo  ( exception.m_sdlErrorInfo )
{
}

const AppWindowException & AppWindowException::operator = (const AppWindowException &exception) noexcept
{
    CommonException::operator = (exception);
    m_window                  = exception.m_window;
    m_sdlErrorInfo            = exception.m_sdlErrorInfo;

    return *this;
}

bool AppWindowException::operator == (const AppWindowException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_window                  == exception.m_window
      && m_sdlErrorInfo            == exception.m_sdlErrorInfo )
    {
        equal = true;
    }

    return equal;
}

bool AppWindowException::operator != (const AppWindowException &exception) const noexcept
{
    return !(*this == exception);
}

void AppWindowException::setWindow(AppWindow *window) noexcept
{
    m_window = window;
}

void AppWindowException::setSDLErrorInfo(const QString &errorInfo) noexcept
{
    m_sdlErrorInfo = errorInfo;
}

const QByteArray & AppWindowException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_window )
    {
        uint status = m_window->getStatus();
        infoString += QString("\n Application window name: \t %1").arg(m_window->getName() )
                   +  QString("\n Application window description: %1").arg(m_window->getDescription() );
        if( !m_window->isCreated() )
        {
            infoString += "\n Window not created.";
        }
        if( !m_window->isRunning() )
        {
            infoString += "\n Window is not running.";
        }
        if( (status & AppWindowStatus::INVALID_EVENTS_HANDLER_POINTER) == AppWindowStatus::INVALID_EVENTS_HANDLER_POINTER )
        {
            infoString += "\n Invalid events handler pointer.";
        }
        if( (status & AppWindowStatus::INVALID_OPENGL_CONTEXT_POINTER) == AppWindowStatus::INVALID_OPENGL_CONTEXT_POINTER )
        {
            infoString += "\n Invalid OpenGL context pointer.";
        }
        if( (status & AppWindowStatus::NO_ENGINE_POINTER) == AppWindowStatus::NO_ENGINE_POINTER )
        {
            infoString += "\n Engine pointer not set.";
        }
        if( (status & AppWindowStatus::INVALID_WINDOW_KEY) == AppWindowStatus::INVALID_WINDOW_KEY )
        {
            infoString += "\n Engine has no window object with provided key.";
        }
        if( !m_sdlErrorInfo.isEmpty() )
        {
            infoString += QString("\n SDL error info: \n %1").arg(m_sdlErrorInfo.trimmed() );
        }
    }

    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
