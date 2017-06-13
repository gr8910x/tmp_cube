#include "programexception.h"
#include "program.h"

using namespace com_defs;

uint ProgramException::counter = 0;

ProgramException::ProgramException() noexcept :
    CommonException (         ),
    m_program       ( nullptr ),
    m_linkingLog    (         )
{
    ++ ProgramException::counter;
    fillInfoBytes();
}

ProgramException::ProgramException( const QString &message ) noexcept :
    CommonException ( message ),
    m_program       ( nullptr ),
    m_linkingLog    (         )

{
    ++ ProgramException::counter;
    fillInfoBytes();
}

ProgramException::ProgramException( Program *program ) noexcept :
    CommonException (         ),
    m_program       ( program ),
    m_linkingLog    (         )
{
    ++ ProgramException::counter;
    fillInfoBytes();
}

ProgramException::ProgramException( Program       *program
                                  , const QString &message ) noexcept :
    CommonException ( message ),
    m_program       ( program ),
    m_linkingLog    (         )
{
    ++ ProgramException::counter;
    fillInfoBytes();
}

ProgramException::ProgramException( Program       *program
                                  , const QString &message
                                  , const QString &linkingLog ) noexcept :
    CommonException ( message    ),
    m_program       ( program    ),
    m_linkingLog    ( linkingLog )
{
    ++ ProgramException::counter;
    fillInfoBytes();
}

ProgramException::ProgramException( const ProgramException &exception ) noexcept:
    CommonException ( exception              ),
    m_program       ( exception.m_program    ),
    m_linkingLog    ( exception.m_linkingLog )
{
}

const ProgramException & ProgramException::operator = (const ProgramException &exception) noexcept
{
    CommonException::operator = (exception);
    m_program                 = exception.m_program;
    m_linkingLog              = exception.m_linkingLog;

    return *this;
}

bool ProgramException::operator == (const ProgramException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_program                 == exception.m_program
      && m_linkingLog              == exception.m_linkingLog )
    {
        equal = true;
    }

    return equal;
}

bool ProgramException::operator != (const ProgramException &exception) const noexcept
{
    return !(*this == exception);
}

void ProgramException::setProgram(Program *program) noexcept
{
    m_program = program;
    fillInfoBytes();
}

void ProgramException::setLinkingLog(const QString &linkingLog) noexcept
{
    m_linkingLog = linkingLog;
    fillInfoBytes();
}

const QByteArray & ProgramException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_program )
    {
        uint status = m_program->getStatus();
        infoString  += QString("\n Program name: \t %1").arg(m_program->getName() )
                    +  QString(". Progran id: \t %1").arg(m_program->getId() )
                    +  QString("\n Program description: %1").arg(m_program->getDescription() );
        if( (status & ProgramStatus::NOT_CREATED) == ProgramStatus::NOT_CREATED )
        {
            infoString += "\n Program not created.";
        }
        if( (status & ProgramStatus::NOT_LINKED) == ProgramStatus::NOT_LINKED )
        {
            infoString += "\n Program not linked.";
        }
        if( !m_linkingLog.isEmpty() )
        {
            infoString += QString("\n Linking log: \n %1").arg(m_linkingLog.trimmed() );
        }
        if( m_program->isUsing() )
        {
            infoString += "\n Program is being used.";
        }
    }

    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
