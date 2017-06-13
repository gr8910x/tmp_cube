#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "commonincludings.h"
#include "shader.h"

//! Implements OpenGL vertex shader.
class VertexShader : public Shader
{
public:
    VertexShader();                                                     //! Default constructor.
    VertexShader( const QString  &path );                               //! Parameterized constructor.
    VertexShader( const QString  &path                                  //! Parameterized constructor.
                , const QString  &description );

    VertexShader( const VertexShader &shader );                         //! Copying constructor.

    virtual ~VertexShader() {}

    virtual GLenum getType() const override { return GL_VERTEX_SHADER; }//! Returns shader type.
    virtual GLuint create() noexcept(false) override;                   //! Creates and compiles shader, returns its id generated by OpenGL.

    const VertexShader & operator = (const VertexShader &shader);       //! Operator " =  ".
    bool  operator == (const VertexShader &shader) const;               //! Operator " == ".
    bool  operator != (const VertexShader &shader) const;               //! Operator " != ".

public:
    static GLuint  getCounter() { return counter; }                     //! Returns number of creates vertex shader objects.

private:
    static GLuint  counter;     //! Counter of created vertex shaders objects.
};

#endif // VERTEXSHADER_H
