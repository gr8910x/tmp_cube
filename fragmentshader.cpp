#include "fragmentshader.h"

using namespace com_defs;

GLuint FragmentShader::counter = 0;

FragmentShader::FragmentShader() :
    Shader (      )
{
    ++ FragmentShader::counter;
}

FragmentShader::FragmentShader( const QString &path ) :
    Shader ( path )
{
    ++ FragmentShader::counter;
}

FragmentShader::FragmentShader( const QString &path
                              , const QString &description ) :
    Shader ( path, description )
{
    ++FragmentShader::counter;
}

FragmentShader::FragmentShader( const FragmentShader &shader ) :
    Shader ( shader )
{
}

GLuint FragmentShader::create() noexcept(false)
{
    return Shader::create(getType() );
}

const FragmentShader & FragmentShader::operator = (const FragmentShader &shader)
{
    Shader::operator = (shader);

    return *this;
}

bool FragmentShader::operator == (const FragmentShader &shader) const
{
    bool equal = false;

    if(  Shader::operator == (shader)
       && getType()       == shader.getType()
      )
    {
        equal = true;
    }

    return equal;
}

bool FragmentShader::operator != (const FragmentShader &shader) const
{
    return !(*this == shader);
}
