#include "shader.h"
#include "shaderexception.h"

using namespace com_defs;

GLuint Shader::counter = 0;

Shader::Shader() :
    m_path        (                                   ),
    m_source      (                                   ),
    m_id          (  0                                ),
    m_description (  "Empty description"              ),
    m_status      (  ShaderStatus::SHADER_NOT_CREATED
                   | ShaderStatus::NO_SHADER_DATA     )
{
    m_name = ++ Shader::counter;
}

Shader::Shader( const QString &path ) noexcept(false) :
    m_path        (  path                             ),
    m_source      (                                   ),
    m_id          (  0                                ),
    m_description (  "Empty description"              ),
    m_status      (  ShaderStatus::SHADER_NOT_CREATED
                   | ShaderStatus::NO_SHADER_DATA     )
{
    m_name = ++ Shader::counter;    
}

Shader::Shader( const QString &path
              , const QString &description
              ) :
    m_path         (  path                             ),
    m_source       (                                   ),
    m_id           (  0                                ),
    m_description  (  description                      ),
    m_status       (  ShaderStatus::SHADER_NOT_CREATED
                    | ShaderStatus::NO_SHADER_DATA     )
{
    m_name = ++ Shader::counter;    
}

Shader::Shader( const Shader &shader ) :
    m_path        ( shader.m_path        ),
    m_source      ( shader.m_source      ),
    m_id          ( shader.m_id          ),
    m_name        ( shader.m_name        ),
    m_description ( shader.m_description ),
    m_status      ( shader.m_status      )
{
}

void Shader::setPath(const QString &path)
{
    m_path = path;
}

void Shader::setDescription(const QString &description)
{
    m_description = description;
}

bool Shader::isCreated() const
{
    return (m_status & ShaderStatus::SHADER_NOT_CREATED) != ShaderStatus::SHADER_NOT_CREATED;
}

GLuint Shader::create(GLenum type) noexcept(false)
{
    ( m_source.isEmpty() ) ? m_status |=  ShaderStatus::NO_SHADER_DATA
                           : m_status &= ~ShaderStatus::NO_SHADER_DATA;

    if( (m_status & ShaderStatus::NO_SHADER_DATA) == ShaderStatus::NO_SHADER_DATA )
    {
        throw ShaderException(this, "Shader exception occured");
    }

    m_id = glCreateShader(type);

    QByteArray shaderBytes = m_source.toUtf8();
    const GLchar *shader = shaderBytes.constData();
    const GLint  shaderLength = m_source.length();
    glShaderSource(m_id, 1, &shader, &shaderLength);
    glCompileShader(m_id);
    int success = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    ( success == GL_FALSE ) ? m_status |=  ShaderStatus::SHADER_NOT_CREATED
                            : m_status &= ~ShaderStatus::SHADER_NOT_CREATED;

    if( (m_status & ShaderStatus::SHADER_NOT_CREATED) == ShaderStatus::SHADER_NOT_CREATED )
    {
        GLint maxLength = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        QVector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(m_id, maxLength, &maxLength, &errorLog[0]);
        QString errorString;

        for( const GLchar &letter: errorLog )
        {
            errorString += letter;
        }

        errorString = errorString.trimmed();

        throw ShaderException(this, "Shader exception occured", errorString);
    }

    return m_id;
}

void Shader::setSource(const QString &source)
{
    m_source = source;

    ( m_source.isEmpty() ) ? m_status |=  ShaderStatus::NO_SHADER_DATA
                           : m_status &= ~ShaderStatus::NO_SHADER_DATA;
}

GLuint Shader::remove(GLuint programId)
{
    GLuint id = m_id;
    if( (m_status & ShaderStatus::SHADER_NOT_CREATED) != ShaderStatus::SHADER_NOT_CREATED )
    {
        glDetachShader(programId, m_id);
        glDeleteShader(m_id);
        m_status |=  ShaderStatus::SHADER_NOT_CREATED;
        m_id = 0;
    }

    return id;
}

const QString & Shader::read() noexcept(false)
{    
    QFile shaderFile(m_path);
    bool opened = shaderFile.open(QIODevice::ReadOnly);

    ( !opened ) ? m_status |=  ShaderStatus::INVALID_SOURCE
                : m_status &= ~ShaderStatus::INVALID_SOURCE;

    if( (m_status & ShaderStatus::INVALID_SOURCE) == ShaderStatus::INVALID_SOURCE )
    {
        throw ShaderException(this, "Shader exception occured");
    }

    QByteArray shaderBytes = shaderFile.readAll();
    shaderFile.close();

    m_source = QString::fromUtf8(shaderBytes);

    ( m_source.isEmpty() ) ? m_status |=  ShaderStatus::NO_SHADER_DATA
                           : m_status &= ~ShaderStatus::NO_SHADER_DATA;

    if( (m_status & ShaderStatus::NO_SHADER_DATA) == ShaderStatus::NO_SHADER_DATA )
    {
        throw ShaderException(this, "Shader exception occured");
    }

    return m_source;
}

const Shader & Shader::operator = (const Shader &shader)
{
    m_path         = shader.m_path;
    m_source       = shader.m_source;

    ( m_source.isEmpty() ) ? m_status |=  ShaderStatus::NO_SHADER_DATA
                           : m_status &= ~ShaderStatus::NO_SHADER_DATA;

    m_description  = shader.m_description;

    return *this;
}

bool Shader::operator == (const Shader &shader) const
{
    bool equal = false;

    if(  m_path       == shader.m_path
      && m_source     == shader.m_source
      )
    {
        equal = true;
    }

    return equal;
}

bool Shader::operator != (const Shader &shader) const
{
    return !(*this == shader);
}
