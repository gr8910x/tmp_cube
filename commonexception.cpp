#include "commonexception.h"

uint CommonException::counter = 0;

CommonException::CommonException() noexcept :
    m_message      ( "Undefined exception message" ),
    m_infoBytes    (                               )
{
    m_name = ++ CommonException::counter;
    fillInfoBytes();
}

CommonException::CommonException(const QString &message) noexcept :
    m_message      ( message               ),
    m_infoBytes    (                       )
{
    m_name = ++ CommonException::counter;
    fillInfoBytes();
}

CommonException::CommonException(const CommonException &exception) noexcept :
    m_message   ( exception.m_message   ),
    m_infoBytes ( exception.m_infoBytes ),
    m_name      ( exception.m_name      )
{    
}

const char * CommonException::what() const noexcept
{
    return m_infoBytes.constData();
}

const CommonException & CommonException::operator = (const CommonException &exception) noexcept
{
    m_message       = exception.m_message;
    m_infoBytes     = exception.m_infoBytes;

    return *this;
}

bool CommonException::operator == (const CommonException &exception) const noexcept
{
    bool equal = false;

    if(  m_message   == exception.m_message
      && m_infoBytes == exception.m_infoBytes )
    {
        equal = true;
    }

    return equal;
}

bool CommonException::operator != (const CommonException &exception) const noexcept
{
    return !(*this == exception);
}

void CommonException::setMessage(const QString &message) noexcept
{
    m_message = message;
    fillInfoBytes();
}

const QByteArray & CommonException::fillInfoBytes() noexcept
{
    m_infoBytes = m_message.toUtf8();
    return m_infoBytes;
}
