#include "shaderexception.h"
#include "shader.h"

using namespace com_defs;

uint ShaderException::counter = 0;

ShaderException::ShaderException() noexcept :
    CommonException  (         ),
    m_shader         ( nullptr ),
    m_compilationLog (         )
{
    ++ ShaderException::counter;
    fillInfoBytes();
}

ShaderException::ShaderException( const QString &message ) noexcept :
    CommonException  ( message ),
    m_shader         ( nullptr ),
    m_compilationLog (         )
{
    ++ ShaderException::counter;
    fillInfoBytes();
}

ShaderException::ShaderException( Shader *shader ) noexcept :
    CommonException  (         ),
    m_shader         ( shader  ),
    m_compilationLog (         )
{
    ++ ShaderException::counter;
    fillInfoBytes();
}

ShaderException::ShaderException( Shader        *shader
                                , const QString &message ) noexcept :
    CommonException  ( message ),
    m_shader         ( shader  ),
    m_compilationLog (         )

{
    ++ ShaderException::counter;
    fillInfoBytes();
}

ShaderException::ShaderException( Shader        *shader
                                , const QString &message
                                , const QString &compilationLog ) noexcept :
    CommonException  ( message        ),
    m_shader         ( shader         ),
    m_compilationLog ( compilationLog )
{
    ++ ShaderException::counter;
    fillInfoBytes();
}

ShaderException::ShaderException( const ShaderException &exception ) noexcept :
    CommonException  ( exception                  ),
    m_shader         ( exception.m_shader         ),
    m_compilationLog ( exception.m_compilationLog )
{
}

const ShaderException & ShaderException::operator = (const ShaderException &exception) noexcept
{
    CommonException::operator = (exception);
    m_shader                  = exception.m_shader;
    m_compilationLog          = exception.m_compilationLog;

    return *this;
}

bool ShaderException::operator == (const ShaderException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_shader                  == exception.m_shader
      && m_compilationLog          == exception.m_compilationLog )
    {
        equal = true;
    }

    return equal;
}

bool ShaderException::operator != (const ShaderException &exception) const noexcept
{
    return !(*this == exception);
}

void ShaderException::setShader( Shader *shader) noexcept
{
    m_shader = shader;
    fillInfoBytes();
}

void ShaderException::setCompilationLog(const QString &compilationLog) noexcept
{
    m_compilationLog = compilationLog;
    fillInfoBytes();
}

const QByteArray & ShaderException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_shader )
    {
        uint status = m_shader->getStatus();
        infoString  += QString("\n Shader name: \t %1").arg(m_shader->getName() )
                    +  QString(". Shader id: \t %1").arg(m_shader->getId() )
                    +  QString("\n Shader description: %1").arg(m_shader->getDescription() )
                    +  QString("\n Shader source code: \n %1").arg(m_shader->getSource().trimmed() );
        if( !m_shader->isCreated() )
        {
            infoString += "\n Shader not created.";
        }
        if( !m_compilationLog.isEmpty() )
        {
            infoString += QString("\n Compilation log: \n %1").arg(m_compilationLog.trimmed() );
        }
        if( (status & ShaderStatus::INVALID_SOURCE) == ShaderStatus::INVALID_SOURCE )
        {
            infoString += "\n Invalid shader source.";
        }
        if( (status & ShaderStatus::NO_SHADER_DATA) == ShaderStatus::NO_SHADER_DATA )
        {
            infoString += "\n Shader data is empty.";
        }
    }
    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
