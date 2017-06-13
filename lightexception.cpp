#include "lightexception.h"
#include "light.h"

using namespace com_defs;

uint LightException::counter = 0;

LightException::LightException() noexcept :
    CommonException  (         ),
    m_light          ( nullptr )
{
    ++ LightException::counter;
    fillInfoBytes();
}

LightException::LightException(const QString &message) noexcept :
    CommonException  ( message ),
    m_light          ( nullptr )
{
    ++ LightException::counter;
    fillInfoBytes();
}

LightException::LightException(Light *light) noexcept :
    CommonException  (        ),
    m_light          ( light  )
{
    ++ LightException::counter;
    fillInfoBytes();
}

LightException::LightException( Light         *light
                              , const QString &message ) noexcept :
    CommonException  ( message ),
    m_light          ( light   )
{
    ++ LightException::counter;
    fillInfoBytes();
}

LightException::LightException(const LightException &exception) noexcept :
    CommonException ( exception         ),
    m_light         ( exception.m_light )
{
}

const LightException  &LightException::operator = (const LightException &exception) noexcept
{
    CommonException::operator = (exception);
    m_light                   = exception.m_light;

    return *this;
}

bool LightException::operator == (const LightException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_light                   == exception.m_light )
    {
        equal = true;
    }

    return equal;
}

bool LightException::operator != (const LightException &exception) const noexcept
{
    return !(*this == exception);
}

const QByteArray & LightException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_light )
    {
        const uint status = m_light->getStatus();
        infoString  += QString("\n Light name: \t %1").arg(m_light->getName() )
                    +  QString("\n Light description: %1").arg(m_light->getDescription() );
        switch (m_light->getType() )
        {
        case LightType::POINT :
            infoString += "\n Light type: point";
            break;
        case LightType::DIRECT :
            infoString += "\n Light type: direct";
            break;
        default :
            infoString += "\n Light type: undefined";
            break;
        }
        if( (status & LightStatus::INVALID_BUFFERS) == LightStatus::INVALID_BUFFERS )
        {
            infoString += QString("\n Mesh buffers were invalid \t %1").arg(NUM_OF_LIGHT_DRAW_ATTEMPTS)
                       +  QString("\t times while trying to draw a light.");
        }
        if( (status & LightStatus::NO_PROGRAM) == LightStatus::NO_PROGRAM )
        {
            infoString += "\n Light shading program not set.";
        }
    }
    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
