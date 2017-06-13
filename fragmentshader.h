#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "commonincludings.h"
#include "shader.h"

//! Implements OpenGL fragment shader.
class FragmentShader : public Shader
{
public:
    FragmentShader();                                                     //! Default constructor.
    FragmentShader( const QString  &path);                                //! Parameterized constructor.
    FragmentShader( const QString  &path                                  //! Parameterized constructor.
                  , const QString  &description );

    FragmentShader( const FragmentShader &shader );                       //! Copying constructor.

    virtual ~FragmentShader() {}

    virtual GLenum getType() const override { return GL_FRAGMENT_SHADER; }//! Returns shader type.
    virtual GLuint create() noexcept(false) override;                     //! Creates and compiles shader, returns its id generated by OpenGL.

    const FragmentShader & operator = (const FragmentShader &shader);     //! Operator " =  ".
    bool  operator == (const FragmentShader &shader) const;               //! Operator " == ".
    bool  operator != (const FragmentShader &shader) const;               //! Operator " != ".

private:
    static GLuint getCounter()  { return counter; }                       //! Returns number of created fragment shaders objects.

private:
    static GLuint  counter;     //! Counter of created fragment shaders objects.
};

#endif // FRAGMENTSHADER_H