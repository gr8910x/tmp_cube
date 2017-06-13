#ifndef RENDEREREXCEPTION_H
#define RENDEREREXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Renderer;
class Scene;

//! Implements exceptions linked with OpenGL renderer.
class RendererException : public CommonException
{
public:
    RendererException() noexcept;                                //! Default constructor.
    RendererException( const QString &message   ) noexcept;      //! Parameterized constructor.
    RendererException( Renderer      *renderer  ) noexcept;      //! Parameterized constructor.
    RendererException( Renderer      *renderer                   //! Parameterized constructor.
                     , const QString &message   ) noexcept;
    RendererException( Renderer      *renderer                   //! Parameterized constructor.
                     , const QString &message
                     , GLenum         fboStatus ) noexcept;

    RendererException( const RendererException &exception ) noexcept;                  //! Copying constructor.

    virtual ~RendererException() {}

    const RendererException & operator = (const RendererException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const RendererException &exception) const noexcept;             //! Operator " == ".
    bool  operator != (const RendererException &exception) const noexcept;             //! Operator " != ".

public:
    const Renderer * getRenderer() const noexcept { return m_renderer; }//! Returns pointer to renderer object where exception occured.
    Renderer * getRenderer() noexcept { return m_renderer; }            //! Returns pointer to renderer object where exception occured, overloaded function.
    void setRenderer(Renderer * renderer) noexcept;                     //! Sets pointer to renderer object where exception occured.

    GLenum getFBOStatus() const noexcept { return m_fboStatus; } //! Returns framebuffer object status enum.
    void setFBOStatus(GLenum fboStatus) noexcept;                //! Sets framebuffer object status enum.

public:
    static uint getCounter() { return counter; }                 //! Returns number of created renderer exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;//! Fills info bytes array with bytes and returns it.

private:
    static uint counter;        //! Counter of created renderer exception objects.

private:
    Renderer *   m_renderer;    //! A pointer to renderer object where exception occured.

    GLenum       m_fboStatus;   //! Framebuffer object status enum.
};

#endif // RENDEREREXCEPTION_H
