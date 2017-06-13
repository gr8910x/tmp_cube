#include "engineexception.h"
#include "engine.h"

using namespace com_defs;

uint EngineException::counter = 0;

EngineException::EngineException() noexcept :
    CommonException (         ),
    m_engine        ( nullptr ),
    m_sdlErrorInfo  (         )
{
    ++ EngineException::counter;
    fillInfoBytes();
}

EngineException::EngineException(const QString &message) noexcept :
    CommonException ( message ),
    m_engine        ( nullptr ),
    m_sdlErrorInfo  (         )
{
    ++ EngineException::counter;
    fillInfoBytes();
}

EngineException::EngineException( Engine *engine ) noexcept:
    CommonException (         ),
    m_engine        ( engine  ),
    m_sdlErrorInfo  (         )
{
    ++ EngineException::counter;
    fillInfoBytes();
}

EngineException::EngineException( Engine         *engine
                                , const QString &message
                                , const QString &sdlErrorInfo ) noexcept :
    CommonException ( message      ),
    m_engine        ( engine       ),
    m_sdlErrorInfo  ( sdlErrorInfo )
{
    ++ EngineException::counter;
    fillInfoBytes();
}

EngineException::EngineException( const EngineException &exception ) noexcept :
    CommonException ( exception                ),
    m_engine        ( exception.m_engine       ),
    m_sdlErrorInfo  ( exception.m_sdlErrorInfo )
{
}

const EngineException & EngineException::operator = (const EngineException &exception) noexcept
{
    EngineException::operator = (exception);
    m_engine                  = exception.m_engine;
    m_sdlErrorInfo            = exception.m_sdlErrorInfo;

    return *this;
}

bool EngineException::operator == (const EngineException &exception) const noexcept
{
    bool equal =false;

    if(  CommonException::operator == (exception)
      && m_engine                  == exception.m_engine
      && m_sdlErrorInfo            == exception.m_sdlErrorInfo
      )
    {
        equal = true;
    }

    return equal;
}

bool EngineException::operator != (const EngineException &exception) const noexcept
{
    return !(*this == exception);
}

void EngineException::setEngine(Engine *engine) noexcept
{
    m_engine = engine;
}

void EngineException::setSDLErrorInfo(const QString &sdlErrorInfo) noexcept
{
    m_sdlErrorInfo = sdlErrorInfo;
}

const QByteArray & EngineException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_engine )
    {
        uint status = m_engine->getStatus();
        infoString += QString("\n Engine name: \t %1").arg(m_engine->getName() )
                   +  QString("\n Engine description: %1").arg(m_engine->getDescription() );
        if( (status & EngineStatus::NOT_INITED) == EngineStatus::NOT_INITED )
        {
            infoString += "\n Engine not initialized.";
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
