#include "openglcontext.h"
#include "appwindow.h"
#include "openglcontextexception.h"
#include "engine.h"
#include "scene.h"

using namespace com_defs;

GLuint OpenGLContext::counter = 0;

OpenGLContext::OpenGLContext() :
    m_clearColor  (                                         ),
    m_clearDepth  (  1.0f                                   ),
    m_engine      (  nullptr                                ),
    m_window      (                                         ),
    m_sdlGLContext(  nullptr                                ),
    m_description (  "Empty description"                    ),
    m_status      (  OpenGLContextStatus::NOT_CREATED
                   | OpenGLContextStatus::NO_ENGINE_POINTER )
{
    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( const QVector4D &clearColor ) :
    m_clearColor  (  clearColor                             ),
    m_clearDepth  (  1.0f                                   ),
    m_engine      (  nullptr                                ),
    m_window      (                                         ),
    m_sdlGLContext(  nullptr                                ),
    m_description (  "Empty description"                    ),
    m_status      (  OpenGLContextStatus::NOT_CREATED
                   | OpenGLContextStatus::NO_ENGINE_POINTER )
{
    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( const QVector4D &clearColor
                            , GLfloat          clearDepth ) :
    m_clearColor  (  clearColor                             ),
    m_clearDepth  (  clearDepth                             ),
    m_engine      (  nullptr                                ),
    m_window      (                                         ),
    m_sdlGLContext(  nullptr                                ),
    m_description (  "Empty description"                    ),
    m_status      (  OpenGLContextStatus::NOT_CREATED
                   | OpenGLContextStatus::NO_ENGINE_POINTER )
{
    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( GLfloat clearRed
                            , GLfloat clearGreen
                            , GLfloat clearBlue
                            , GLfloat clearAlpha ) :
    m_clearColor  (  clearRed, clearGreen, clearBlue, clearAlpha ),
    m_clearDepth  (  1.0f                                        ),
    m_engine      (  nullptr                                     ),
    m_window      (                                              ),
    m_sdlGLContext(  nullptr                                     ),
    m_description (  "Empty description"                         ),
    m_status      (  OpenGLContextStatus::NOT_CREATED
                   | OpenGLContextStatus::NO_ENGINE_POINTER      )
{
    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( GLfloat clearRed
                            , GLfloat clearGreen
                            , GLfloat clearBlue
                            , GLfloat clearAlpha
                            , GLfloat clearDepth ) :
    m_clearColor  (  clearRed, clearGreen, clearBlue, clearAlpha ),
    m_clearDepth  (  clearDepth                                  ),
    m_engine      (  nullptr                                     ),
    m_window      (                                              ),
    m_sdlGLContext(  nullptr                                     ),
    m_description (  "Empty description"                         ),
    m_status      (  OpenGLContextStatus::NOT_CREATED
                   | OpenGLContextStatus::NO_ENGINE_POINTER      )
{
    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( Engine *engine ) :
    m_clearColor  (                                  ),
    m_clearDepth  ( 1.0f                             ),
    m_engine      ( engine                           ),
    m_window      (                                  ),
    m_sdlGLContext( nullptr                          ),
    m_description ( "Empty description"              ),
    m_status      ( OpenGLContextStatus::NOT_CREATED )
{
    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;

    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( Engine                   *engine
                            , std::weak_ptr<AppWindow>  window ) :
    m_clearColor  (                                  ),
    m_clearDepth  ( 1.0f                             ),
    m_engine      ( engine                           ),
    m_window      ( window                           ),
    m_sdlGLContext( nullptr                          ),
    m_description ( "Empty description"              ),
    m_status      ( OpenGLContextStatus::NOT_CREATED )
{
    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;

    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( const QVector4D          &clearColor
                            , GLfloat                   clearDepth
                            , Engine                   *engine
                            , std::weak_ptr<AppWindow>  window
                            , const QString            &description ) :
    m_clearColor  ( clearColor                       ),
    m_clearDepth  ( clearDepth                       ),
    m_engine      ( engine                           ),
    m_window      ( window                           ),
    m_sdlGLContext( nullptr                          ),
    m_description ( description                      ),
    m_status      ( OpenGLContextStatus::NOT_CREATED )
{
    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;

    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::OpenGLContext( GLfloat                   clearRed
                            , GLfloat                   clearGreen
                            , GLfloat                   clearBlue
                            , GLfloat                   clearAlpha
                            , GLfloat                   clearDepth
                            , Engine                   *engine
                            , std::weak_ptr<AppWindow>  window
                            , const QString            &description ) :
    m_clearColor  ( clearRed, clearGreen, clearBlue, clearAlpha ),
    m_clearDepth  ( clearDepth                                  ),
    m_engine      ( engine                                      ),
    m_window      ( window                                      ),
    m_sdlGLContext( nullptr                                     ),
    m_description ( description                                 ),
    m_status      ( OpenGLContextStatus::NOT_CREATED            )
{
    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;

    m_name = ++ OpenGLContext::counter;
}

OpenGLContext::~OpenGLContext()
{
    destroy();
}

void OpenGLContext::create() noexcept(false)
{
    if( !isCreated() )
    {
        ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER    // Checking engine pointer.
                      :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;
        if( (m_status & OpenGLContextStatus::NO_ENGINE_POINTER) == OpenGLContextStatus::NO_ENGINE_POINTER )
        {
            throw OpenGLContextException(this, "OpenGL context exception occured");
        }

        std::shared_ptr<AppWindow> window = m_window.lock();

        ( !window ) ? m_status |=  OpenGLContextStatus::INVALID_WINDOW_POINTER // Checking pointer to window.
                    : m_status &= ~OpenGLContextStatus::INVALID_WINDOW_POINTER;
        if( (m_status & OpenGLContextStatus::INVALID_WINDOW_POINTER) == OpenGLContextStatus::INVALID_WINDOW_POINTER )
        {
            throw OpenGLContextException(this, "OpenGL context exception occured");
        }

        m_sdlGLContext = SDL_GL_CreateContext(window->getSDLWindow() );   // Creating SDL OpneGL context.
        ( !m_sdlGLContext ) ? m_status |=  OpenGLContextStatus::NOT_CREATED
                            : m_status &= ~OpenGLContextStatus::NOT_CREATED;
        if( !isCreated() )
        {
            QString sdlError(SDL_GetError() );
            throw OpenGLContextException(this, "OpenGL context exception occured", sdlError);
        }

        GLenum glewStatus = aux_funcs::initGLEW();  // Initializing GLEW library.
        ( glewStatus != GLEW_OK ) ? m_status |=  OpenGLContextStatus::INVALID_GLEW_INITIALIZATION
                                  : m_status &= ~OpenGLContextStatus::INVALID_GLEW_INITIALIZATION;
        if( (m_status & OpenGLContextStatus::INVALID_GLEW_INITIALIZATION) == OpenGLContextStatus::INVALID_GLEW_INITIALIZATION )
        {
            const uchar *glewError = glewGetErrorString(glewStatus);
            uint length = strlen(reinterpret_cast<const char *>(glewError) );
            QVector<QChar> letters(length);
            uint i = 0;
            for( QChar &letter : letters )
            {
                letter = QChar(glewError[i]);
                ++ i;
            }
            QString glewErrorString(letters.constData(), length);
            throw OpenGLContextException(this, "OpenGL context exception occured", "", glewErrorString);
        }

        glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w() );
        glClearDepth(m_clearDepth);
        glDepthFunc(GL_LESS);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);

        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }
}

void OpenGLContext::draw() noexcept(false)
{
    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER    // Checking engine pointer.
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;
    if( (m_status & OpenGLContextStatus::NO_ENGINE_POINTER) == OpenGLContextStatus::NO_ENGINE_POINTER )
    {
        throw OpenGLContextException(this, "OpenGL context exception occured");
    }

    std::shared_ptr<Scene> selectedScene = m_engine->getContext().getSelectedScene().lock(); // Receiving active scene.
    selectedScene->getRenderer().renderGBuffer();   // Rendering geometry buffer.
    selectedScene->getRenderer().renderLBuffer();   // Rendering light buffer.
    selectedScene->getRenderer().postProcess();     // Post processing.
    selectedScene->getRenderer().finalRender();     // Final rendering.

    glFlush();                      // Flush OpenGL framebuffer.
}

void OpenGLContext::destroy()
{
    if( (m_status & OpenGLContextStatus::NOT_CREATED) != OpenGLContextStatus::NOT_CREATED ) // Checking if OpenGL context was created.
    {
        m_status |= OpenGLContextStatus::NOT_CREATED;

        SDL_GL_DeleteContext(m_sdlGLContext); // Deleting SDL OpenGL context.
    }
}

void OpenGLContext::makeCurrent() noexcept(false)
{
    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER    // Checking engine pointer.
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;
    if( (m_status & OpenGLContextStatus::NO_ENGINE_POINTER) == OpenGLContextStatus::NO_ENGINE_POINTER )
    {
        throw OpenGLContextException(this, "OpenGL context exception occured");
    }

    std::shared_ptr<AppWindow> window = m_window.lock();

    ( !window ) ? m_status |=  OpenGLContextStatus::INVALID_WINDOW_POINTER // Checking pointer to window.
                : m_status &= ~OpenGLContextStatus::INVALID_WINDOW_POINTER;
    if( (m_status & OpenGLContextStatus::INVALID_WINDOW_POINTER) == OpenGLContextStatus::INVALID_WINDOW_POINTER )
    {
        throw OpenGLContextException(this, "OpenGL context exception occured");
    }

    int success = SDL_GL_MakeCurrent(window->getSDLWindow(), m_sdlGLContext); // Setting up OpenGL context rendering into an SDL OpenGL window.
    ( success < 0 ) ? m_status |=  OpenGLContextStatus::INVALID_MAKING_CURRENT // Checking for SDL errors.
                    : m_status &= ~OpenGLContextStatus::INVALID_MAKING_CURRENT;
    if( (m_status & OpenGLContextStatus::INVALID_MAKING_CURRENT) == OpenGLContextStatus::INVALID_MAKING_CURRENT )
    {
        QString sdlError(SDL_GetError() );
        throw OpenGLContextException(this, "OpenGL context exception occured", sdlError);
    }
}

const OpenGLContext & OpenGLContext::operator = (const OpenGLContext &context)
{
    m_clearColor  = context.m_clearColor;
    m_clearDepth  = context.m_clearDepth;
    m_engine      = context.m_engine;

    m_description = context.m_description;

    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;

    return *this;
}

bool OpenGLContext::operator == (const OpenGLContext &context) const
{
    bool equal = false;

    if(  m_clearColor     == context.m_clearColor
      && m_clearDepth     == context.m_clearDepth
      && m_engine         == context.m_engine

      )
    {
        equal = true;
    }

    return equal;
}

bool OpenGLContext::operator != (const OpenGLContext &context) const
{
    return !(*this == context);
}

void OpenGLContext::setClearColor(const QVector4D &clearColor)
{
    m_clearColor = clearColor;
    if( isCreated() )
    {
        glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w() );
    }
}

void OpenGLContext::setClearRed(GLfloat red)
{
    m_clearColor.setX(red);
    if( isCreated() )
    {
        glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w() );
    }
}

void OpenGLContext::setClearGreen(GLfloat green)
{
    m_clearColor.setY(green);
    if( isCreated() )
    {
        glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w() );
    }
}

void OpenGLContext::setClearBlue(GLfloat blue)
{
    m_clearColor.setZ(blue);
    if( isCreated() )
    {
        glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w() );
    }
}

void OpenGLContext::setClearAlpha(GLfloat alpha)
{
    m_clearColor.setW(alpha);
    if( isCreated() )
    {
        glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w() );
    }
}

void OpenGLContext::setClearDepth(GLfloat clearDepth)
{
    m_clearDepth = clearDepth;
    if( isCreated() )
    {
        glClearDepth(m_clearDepth);
    }
}

void OpenGLContext::setEngine(Engine *engine)
{
    m_engine = engine;

    ( !m_engine ) ?  m_status |=  OpenGLContextStatus::NO_ENGINE_POINTER
                  :  m_status &= ~OpenGLContextStatus::NO_ENGINE_POINTER;
}

void OpenGLContext::setWindow(std::weak_ptr<AppWindow> window)
{
    m_window = window;
}

void OpenGLContext::setDescription(const QString &description)
{
    m_description = description;
}

bool OpenGLContext::isCreated() const
{
    return (m_status & OpenGLContextStatus::NOT_CREATED) != OpenGLContextStatus::NOT_CREATED;
}

std::shared_ptr<OpenGLContext> OpenGLContext::createObject()
{
    return std::make_shared<OpenGLContext>();
}

OpenGLContext::OpenGLContext( const OpenGLContext &context ) :
    m_clearColor  ( context.m_clearColor   ),
    m_clearDepth  ( context.m_clearDepth   ),
    m_engine      ( context.m_engine       ),
    m_window      ( context.m_window       ),
    m_sdlGLContext( context.m_sdlGLContext ),
    m_name        ( context.m_name         ),
    m_description ( context.m_description  ),
    m_status      ( context.m_status       )
{
}
