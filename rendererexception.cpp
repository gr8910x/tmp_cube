#include "rendererexception.h"
#include "renderer.h"
#include "scene.h"

using namespace com_defs;

uint RendererException::counter = 0;

RendererException::RendererException() noexcept :
    CommonException (             ),
    m_renderer      ( nullptr     ),
    m_fboStatus     ( GL_NO_ERROR )
{
    ++ RendererException::counter;
    fillInfoBytes();
}

RendererException::RendererException( const QString &message ) noexcept :
    CommonException ( message     ),
    m_renderer      ( nullptr     ),
    m_fboStatus     ( GL_NO_ERROR )
{
    ++ RendererException::counter;
    fillInfoBytes();
}

RendererException::RendererException( Renderer *renderer ) noexcept :
    CommonException (             ),
    m_renderer      ( renderer    ),
    m_fboStatus     ( GL_NO_ERROR )
{
    ++ RendererException::counter;
    fillInfoBytes();
}

RendererException::RendererException( Renderer      *renderer
                                    , const QString &message ) noexcept :
    CommonException ( message     ),
    m_renderer      ( renderer    ),
    m_fboStatus     ( GL_NO_ERROR )
{
    ++ RendererException::counter;
    fillInfoBytes();
}

RendererException::RendererException( Renderer      *renderer
                                    , const QString &message
                                    , GLenum         fboStatus ) noexcept :
    CommonException ( message    ),
    m_renderer      ( renderer   ),
    m_fboStatus     ( fboStatus  )
{
    ++ RendererException::counter;
    fillInfoBytes();
}

RendererException::RendererException( const RendererException &exception ) noexcept:
    CommonException ( exception             ),
    m_renderer      ( exception.m_renderer  ),
    m_fboStatus     ( exception.m_fboStatus )
{
}

const RendererException & RendererException::operator = (const RendererException &exception) noexcept
{
    CommonException::operator = (exception);
    m_renderer                = exception.m_renderer;
    m_fboStatus               = exception.m_fboStatus;

    return *this;
}

bool RendererException::operator ==(const RendererException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_renderer                == exception.m_renderer
      && m_fboStatus               == exception.m_fboStatus )
    {
        equal = true;
    }

    return equal;
}

bool RendererException::operator != (const RendererException &exception) const noexcept
{
    return !(*this == exception);
}

void RendererException::setRenderer(Renderer *renderer) noexcept
{
    m_renderer = renderer;
}

void RendererException::setFBOStatus(GLenum fboStatus) noexcept
{
    m_fboStatus = fboStatus;
}

const QByteArray & RendererException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_renderer )
    {
        uint status = m_renderer->getStatus();
        infoString  += QString("\n Renderer name: \t %1").arg(m_renderer->getName() )
                    +  QString(". FBO id: \t %1").arg(m_renderer->getFBOId() )
                    +  QString("\n Renderer description: %1").arg(m_renderer->getDescription() )
                    +  QString("\n Scene name: \t %1").arg(m_renderer->getScene()->getName() )
                    +  QString("\n Scene description: %1").arg(m_renderer->getScene()->getDescription() );
        if( (status & RendererStatus::BUFFERS_NOT_GENERATED) == RendererStatus::BUFFERS_NOT_GENERATED )
        {
            infoString += "\n Renderer FBO and textures were not generated.";
        }
        if( (status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
        {
            infoString += "\n Renderer has no scene pointer.";
        }
        if( (status & RendererStatus::INVALID_RECTANGLE_BUFFERS) == RendererStatus::INVALID_RECTANGLE_BUFFERS )
        {
            infoString += QString("\n Renderer rectangle mesh buffers were invalid \t %1").arg(NUM_OF_RENDERER_RECT_DRAW_ATTEMPTS)
                       +  QString("\t times while trying to draw renderer rectangle.");
        }
        if( (status & RendererStatus::NO_RENDERER_PROGRAM) == RendererStatus::NO_RENDERER_PROGRAM )
        {
            infoString += "\n Renderer has no rendering shading program.";
        }
        if( (status & RendererStatus::FBO_NOT_COMPLETED) == RendererStatus::FBO_NOT_COMPLETED )
        {
            infoString += "\n Renderer FBO was not completed.";
            infoString += QString(" FBO status is: \t %1").arg(m_renderer->getStatus() );

            switch( m_fboStatus )
            {
            case GL_FRAMEBUFFER_UNDEFINED:
                infoString += "\n GL_FRAMEBUFFER_UNDEFINED"
                              ", target is the default framebuffer, but the default framebuffer does not exist.";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                infoString += "\n GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"
                              ", some of the framebuffer attachment points are framebuffer incomplete.";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                infoString += "\n GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"
                              ", framebuffer does not have at least one image attached to it.";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                infoString += "\n GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"
                              ", value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi.";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                infoString += "\n GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"
                              ", GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.";
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                infoString += "\n GL_FRAMEBUFFER_UNSUPPORTED"
                              ", the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                infoString += "\n GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"
                              ", the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; or the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES"
                              ", or the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                infoString += "\n GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"
                              ", some framebuffer attachment is layered, and any populated attachment is not layered, or all populated color attachments are not from textures of the same target.";
                break;
            default:
                infoString += "\n Undefined framebuffer status.";
                break;
            }
        }
    }

    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
