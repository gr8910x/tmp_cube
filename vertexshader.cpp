#include "vertexshader.h"

using namespace com_defs;

GLuint VertexShader::counter = 0;

VertexShader::VertexShader() :
    Shader(       )
{
    ++ VertexShader::counter;
}

VertexShader::VertexShader( const QString &path ) :
    Shader ( path  )
{
    ++ VertexShader::counter;
}

VertexShader::VertexShader( const QString &path
                          , const QString &description ) :
    Shader ( path, description  )
{
    ++ VertexShader::counter;
}

VertexShader::VertexShader( const VertexShader &shader ) :
    Shader ( shader )
{
}

GLuint VertexShader::create() noexcept(false)
{
    return Shader::create(getType() );
}

const VertexShader & VertexShader::operator = (const VertexShader &shader)
{
    Shader::operator = (shader);

    return *this;
}

bool VertexShader::operator == (const VertexShader &shader) const
{
    bool equal = false;

    if(  Shader::operator == (shader)
      && getType()        == shader.getType()
      )
    {
        equal = true;
    }

    return equal;
}

bool VertexShader::operator != (const VertexShader &shader) const
{
    return !(*this == shader);
}
