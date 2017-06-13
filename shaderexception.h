#ifndef SHADEREXCEPTION_H
#define SHADEREXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Shader;

//! Implements exceptions linked with OpenGL shaders objects.
class ShaderException : public CommonException
{
public:
    ShaderException() noexcept;                                                    //! Default constructor.
    ShaderException( const QString &message ) noexcept;                            //! Parameterized constructor.
    ShaderException( Shader        *shader  ) noexcept;                            //! Parameterized constructor.
    ShaderException( Shader        *shader                                         //! Parameterized constructor.
                   , const QString &message ) noexcept;
    ShaderException( Shader        *shader                                         //! Parameterized constructor.
                   , const QString &message
                   , const QString &compilationLog ) noexcept;

    ShaderException( const ShaderException &exception ) noexcept;                  //! Copying constructor.

    virtual ~ShaderException() {}

    const ShaderException & operator = (const ShaderException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const ShaderException &exception) const noexcept;           //! Operator " == ".
    bool  operator != (const ShaderException &exception) const noexcept;           //! Operator " != ".

public:
    const Shader * getShader() const noexcept { return m_shader; }                 //! Returns pointer to shader object where exception occured.
    Shader * getShader() noexcept { return m_shader; }                             //! Returns pointer to shader object where exception occured, overloaded function.
    void  setShader(Shader *shader) noexcept;                                      //! Sets pointer to shader object where exception occured.

    const QString & getCompilationLog() const noexcept { return m_compilationLog; }//! Returns shader compilation log string.
    void  setCompilationLog(const QString &compilationLog) noexcept;               //! Sets shader compilation log string.

public:
    static uint  getCounter() { return counter; }                                  //! Returns number of created shader exceptions objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;                  //! Fills info bytes array with bytes and returns it.

private:
    static uint  counter;                //! Counter of created shader exception objects.

private:
    Shader *            m_shader;        //! A pointer to shader object where exception occured.

    QString             m_compilationLog;//! Shader compilation log string.
};

#endif // SHADEREXCEPTION_H
