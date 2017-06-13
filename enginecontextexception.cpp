#include "enginecontextexception.h"
#include "enginecontext.h"

using namespace com_defs;

uint EngineContextException::counter = 0;

EngineContextException::EngineContextException() noexcept :
    CommonException (         ),
    m_context       ( nullptr )
{
    ++ EngineContextException::counter;
    fillInfoBytes();
}

EngineContextException::EngineContextException( EngineContext *context ) noexcept :
    CommonException (         ),
    m_context       ( context )
{
    ++ EngineContextException::counter;
    fillInfoBytes();
}

EngineContextException::EngineContextException(const QString &message) noexcept :
    CommonException ( message ),
    m_context       ( nullptr )
{
    ++ EngineContextException::counter;
    fillInfoBytes();
}

EngineContextException::EngineContextException( EngineContext *context
                                              , const QString &message ) noexcept :
    CommonException ( message ),
    m_context       ( context )
{
    ++ EngineContextException::counter;
    fillInfoBytes();
}

EngineContextException::EngineContextException( const EngineContextException &exception ) noexcept :
    CommonException ( exception                ),
    m_context       ( exception.m_context      )
{
}

const EngineContextException & EngineContextException::operator = (const EngineContextException &exception) noexcept
{
    CommonException::operator = (exception);
    m_context                 = exception.m_context;

    return *this;
}

bool EngineContextException::operator ==(const EngineContextException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_context                 == exception.m_context
      )
    {
        equal = true;
    }

    return equal;
}

bool EngineContextException::operator != (const EngineContextException &exception) const noexcept
{
    return !(*this == exception);
}

void EngineContextException::setEngineContext(EngineContext *context) noexcept
{
    m_context = context;
}

const QByteArray &EngineContextException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_context )
    {
        uint status = m_context->getStatus();
        infoString += QString("\n Engine context name: \t %1").arg(m_context->getName() )
                   +  QString("\n Engine context description: %1").arg(m_context->getDescription() );
        if( !m_context->isSelectedOpenGLContextReady() )
        {
            infoString += "\n Selected OpenGL context not ready or not selected.";
        }
        if( (status & EngineContextStatus::INVALID_SELECTED_OPENGL_CONTEXT) == EngineContextStatus::INVALID_SELECTED_OPENGL_CONTEXT )
        {
            infoString += "\n Selected OpenGL context pointer is invalid.";
        }
        if( (status & EngineContextStatus::INVALID_SELECTED_SCENE) == EngineContextStatus::INVALID_SELECTED_SCENE )
        {
            infoString += "\n Selected scene pointer is invalid.";
        }
        if( (status & EngineContextStatus::INVALID_SELECTED_WINDOW) == EngineContextStatus::INVALID_SELECTED_WINDOW )
        {
            infoString += "\n Selected application window pointer is invalid.";
        }
        if( (status & EngineContextStatus::INVALID_SHAPES_FACTORY) == EngineContextStatus::INVALID_SHAPES_FACTORY )
        {
            infoString += "\n Invalid shapes factory.";
        }
        if( (status & EngineContextStatus::INVALID_SCENES_FACTORY) == EngineContextStatus::INVALID_SCENES_FACTORY )
        {
            infoString += "\n Invalid scenes factory.";
        }
        if( (status & EngineContextStatus::INVALID_PROGRAMS_FACTORY) == EngineContextStatus::INVALID_PROGRAMS_FACTORY )
        {
            infoString += "\n Invalid programs factory.";
        }
        if( (status & EngineContextStatus::INVALID_EVENTS_HANDLERS_FACTORY) == EngineContextStatus::INVALID_EVENTS_HANDLERS_FACTORY )
        {
            infoString += "\n Invalid events handlers factory.";
        }
        if( (status & EngineContextStatus::INVALID_WINDOWS_FACTORY) == EngineContextStatus::INVALID_WINDOWS_FACTORY )
        {
            infoString += "\n Invalid windows factory.";
        }
        if( (status & EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY) == EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY )
        {
            infoString += "\n Invalid OpenGL contexts factory";
        }
        if( (status & EngineContextStatus::INVALID_POINT_LIGHTS_FACTORY) == EngineContextStatus::INVALID_POINT_LIGHTS_FACTORY )
        {
            infoString += "\n Invalid point lights factory";
        }
        if( (status & EngineContextStatus::INVALID_DIRECT_LIGHTS_FACTORY) == EngineContextStatus::INVALID_DIRECT_LIGHTS_FACTORY )
        {
            infoString += "\n Invalid direct lights factory";
        }
    }

    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
