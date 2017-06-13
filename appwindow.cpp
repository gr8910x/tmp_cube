#include "appwindow.h"
#include "appwindowexception.h"
#include "eventshandler.h"
#include "openglcontext.h"
#include "engine.h"

using namespace com_defs;

uint AppWindow::counter = 0;

AppWindow::AppWindow() :
    m_key                  (                                     ),
    m_title                (  "Empty title"                      ),
    m_x                    (  SDL_WINDOWPOS_UNDEFINED            ),
    m_y                    (  SDL_WINDOWPOS_UNDEFINED            ),
    m_width                (  640                                ),
    m_height               (  480                                ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (                                     ),
    m_openGLContext        (                                     ),
    m_engine               (  nullptr                            ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                  ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  "Empty Description"                ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( const QString &title ) :
    m_key                  (                                     ),
    m_title                (  title                              ),
    m_x                    (  SDL_WINDOWPOS_UNDEFINED            ),
    m_y                    (  SDL_WINDOWPOS_UNDEFINED            ),
    m_width                (  640                                ),
    m_height               (  480                                ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (                                     ),
    m_openGLContext        (                                     ),
    m_engine               (  nullptr                            ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                  ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  "Empty Description"                ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( int width
                    , int height ) :
    m_key                  (                                     ),
    m_title                (  "Empty title"                      ),
    m_x                    (  SDL_WINDOWPOS_UNDEFINED            ),
    m_y                    (  SDL_WINDOWPOS_UNDEFINED            ),
    m_width                (  width                              ),
    m_height               (  height                             ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (                                     ),
    m_openGLContext        (                                     ),
    m_engine               (  nullptr                            ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                  ),
    m_sdlRendererInitFlags(   SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  "Empty Description"                ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( int x
                    , int y
                    , int width
                    , int height ) :
    m_key                  (                                     ),
    m_title                (  "Empty title"                      ),
    m_x                    (  x                                  ),
    m_y                    (  y                                  ),
    m_width                (  width                              ),
    m_height               (  height                             ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (                                     ),
    m_openGLContext        (                                     ),
    m_engine               (  nullptr                            ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                  ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  "Empty Description"                ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( const QString &title
                    , int            x
                    , int            y
                    , int            width
                    , int            height ) :
    m_key                  (                                      ),
    m_title                (  title                               ),
    m_x                    (  x                                   ),
    m_y                    (  y                                   ),
    m_width                (  width                               ),
    m_height               (  height                              ),
    m_sdlWindow            (  nullptr                             ),
    m_sdlRenderer          (  nullptr                             ),
    m_eventsHandler        (                                      ),
    m_openGLContext        (                                      ),
    m_engine               (  nullptr                             ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                   ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC           ),
    m_description          (  "Empty Description"                 ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER  )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( const QString                &title
                    , int                           x
                    , int                           y
                    , int                           width
                    , int                           height
                    , std::weak_ptr<EventsHandler>  eventsHandler ) :
    m_key                  (                                     ),
    m_title                (  title                              ),
    m_x                    (  x                                  ),
    m_y                    (  y                                  ),
    m_width                (  width                              ),
    m_height               (  height                             ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (  eventsHandler                      ),
    m_openGLContext        (                                     ),
    m_engine               (  nullptr                            ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                  ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  "Empty Description"                ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( const QString                &title
                    , int                           x
                    , int                           y
                    , int                           width
                    , int                           height
                    , Engine                       *engine
                    , std::weak_ptr<EventsHandler>  eventsHandler
                    , const QString                &description ) :
    m_key                  (                                     ),
    m_title                (  title                              ),
    m_x                    (  x                                  ),
    m_y                    (  y                                  ),
    m_width                (  width                              ),
    m_height               (  height                             ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (  eventsHandler                      ),
    m_openGLContext        (                                     ),
    m_engine               (  engine                             ),
    m_sdlWindowInitFlags   (  SDL_WINDOW_SHOWN
                            | SDL_WINDOW_OPENGL                  ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  description                        ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    ( !m_engine ) ?  m_status |=  AppWindowStatus::NO_ENGINE_POINTER
                  :  m_status &= ~AppWindowStatus::NO_ENGINE_POINTER;

    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( const QString &title
                    , int            x
                    , int            y
                    , int            width
                    , int            height
                    , std::weak_ptr<EventsHandler> eventsHandler
                    , Uint32         sdlWindowInitFlags
                    , const QString &description ) :
    m_key                  (                                     ),
    m_title                (  title                              ),
    m_x                    (  x                                  ),
    m_y                    (  y                                  ),
    m_width                (  width                              ),
    m_height               (  height                             ),
    m_sdlWindow            (  nullptr                            ),
    m_sdlRenderer          (  nullptr                            ),
    m_eventsHandler        (  eventsHandler                      ),
    m_openGLContext        (                                     ),
    m_engine               (  nullptr                            ),
    m_sdlWindowInitFlags   (  sdlWindowInitFlags                 ),
    m_sdlRendererInitFlags (  SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC          ),
    m_description          (  description                        ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING
                            | AppWindowStatus::NO_ENGINE_POINTER )
{
    m_name = ++ AppWindow::counter;
}

AppWindow::AppWindow( const QString &key
                    , const QString &title
                    , int            x
                    , int            y
                    , int            width
                    , int            height
                    , Engine        *engine
                    , std::weak_ptr<EventsHandler> eventsHandler
                    , Uint32         sdlWindowInitFlags
                    , Uint32         sdlRendererInitFlags
                    , const QString &description ) :
    m_key                  (  key                          ),
    m_title                (  title                        ),
    m_x                    (  x                            ),
    m_y                    (  y                            ),
    m_width                (  width                        ),
    m_height               (  height                       ),
    m_sdlWindow            (  nullptr                      ),
    m_sdlRenderer          (  nullptr                      ),
    m_eventsHandler        (  eventsHandler                ),
    m_openGLContext        (                               ),
    m_engine               (  engine                       ),
    m_sdlWindowInitFlags   (  sdlWindowInitFlags           ),
    m_sdlRendererInitFlags (  sdlRendererInitFlags         ),
    m_description          (  description                  ),
    m_status               (  AppWindowStatus::NOT_CREATED
                            | AppWindowStatus::NOT_RUNNING )
{
    ( !m_engine ) ?  m_status |=  AppWindowStatus::NO_ENGINE_POINTER
                  :  m_status &= ~AppWindowStatus::NO_ENGINE_POINTER;

    m_name = ++ AppWindow::counter;
}

AppWindow::~AppWindow()
{
    destroy();
}

void AppWindow::create() noexcept(false)
{
    if( !isCreated() )
    {
        ( !m_engine ) ?  m_status |=  AppWindowStatus::NO_ENGINE_POINTER    // Checking engine pointer.
                      :  m_status &= ~AppWindowStatus::NO_ENGINE_POINTER;
        if( (m_status & AppWindowStatus::NO_ENGINE_POINTER) == AppWindowStatus::NO_ENGINE_POINTER )
        {
            throw AppWindowException(this, "Application window exception occured");
        }

        QByteArray titleBytes = m_title.toUtf8();
        m_sdlWindow = SDL_CreateWindow( titleBytes.constData()  // Creating window.
                                      , m_x
                                      , m_y
                                      , m_width
                                      , m_height
                                      , m_sdlWindowInitFlags );

        ( !m_sdlWindow ) ? m_status |=  AppWindowStatus::NOT_CREATED
                         : m_status &= ~AppWindowStatus::NOT_CREATED;

        if( (m_status & AppWindowStatus::NOT_CREATED) == AppWindowStatus::NOT_CREATED )
        {            
            QString sdlError(SDL_GetError() );
            throw AppWindowException(this, "Application window exception occured", sdlError);
        }


        m_sdlRenderer = SDL_CreateRenderer( m_sdlWindow         // Creating renderer.
                                          , -1
                                          , m_sdlRendererInitFlags );

        ( !m_sdlRenderer ) ? m_status |=  AppWindowStatus::NOT_CREATED
                           : m_status &= ~AppWindowStatus::NOT_CREATED;

        if( (m_status & AppWindowStatus::NOT_CREATED) == AppWindowStatus::NOT_CREATED )
        {
            QString sdlError(SDL_GetError() );
            throw AppWindowException(this, "Application window exception occured", sdlError);
        }

    }
}

void AppWindow::run() noexcept(false)
{
    if( !isRunning() )
    {
        ( !m_engine ) ?  m_status |=  AppWindowStatus::NO_ENGINE_POINTER    // Checking engine pointer.
                      :  m_status &= ~AppWindowStatus::NO_ENGINE_POINTER;
        if( (m_status & AppWindowStatus::NO_ENGINE_POINTER) == AppWindowStatus::NO_ENGINE_POINTER )
        {
            throw AppWindowException(this, "Application window exception occured");
        }

        bool keyValid = m_engine->getContext().getAllWindows().contains(m_key); // Checking window key.
        ( !keyValid ) ?  m_status |=  AppWindowStatus::INVALID_WINDOW_KEY
                      :  m_status &= ~AppWindowStatus::INVALID_WINDOW_KEY;
        if( (m_status & AppWindowStatus::INVALID_WINDOW_KEY) == AppWindowStatus::INVALID_WINDOW_KEY )
        {
            throw AppWindowException(this, "Application window exception occured");
        }

        std::shared_ptr<EventsHandler> eventsHandler = m_eventsHandler.lock();
        std::shared_ptr<OpenGLContext> openGLContext = m_openGLContext.lock();

        ( !eventsHandler ) ? m_status |=  AppWindowStatus::INVALID_EVENTS_HANDLER_POINTER
                           : m_status &= ~AppWindowStatus::INVALID_EVENTS_HANDLER_POINTER;
        ( !openGLContext ) ? m_status |=  AppWindowStatus::INVALID_OPENGL_CONTEXT_POINTER
                           : m_status &= ~AppWindowStatus::INVALID_OPENGL_CONTEXT_POINTER;

        if( (m_status & (  AppWindowStatus::INVALID_EVENTS_HANDLER_POINTER
                         | AppWindowStatus::INVALID_OPENGL_CONTEXT_POINTER
                         | AppWindowStatus::NOT_CREATED                   ))
                     == (  AppWindowStatus::INVALID_EVENTS_HANDLER_POINTER
                         | AppWindowStatus::INVALID_OPENGL_CONTEXT_POINTER
                         | AppWindowStatus::NOT_CREATED                   ))
        {
            throw AppWindowException(this, "Application window exception occured");
        }

        m_status &= ~AppWindowStatus::NOT_RUNNING;      // Removing  AppWindowStatus::NOT_RUNNING  flag.


        std::shared_ptr<AppWindow> window = m_engine->getContext().getWindow(m_key).lock(); // Receiving window smart pointer.
        std::function<QString ()> drawer = [eventsHandler, window, openGLContext] () -> QString {   // Window drawer lambda.

            while( window->isRunning() )
            {
                eventsHandler->handle(window.get() );    // Handle window events.

                openGLContext->draw();          // Draw OpenGL context.


                SDL_GL_SwapWindow(window->getSDLWindow() ); // Updating window with OpenGL rendering.
            }

            window->getEngine()->getContext().removeWindow(window->getKey() );  // Removing window from engine.

            return QString("Events handler task finished.");
        };



        m_engine->getTasksManager().start(drawer); // Starting window drawer lambda as deferred task.
    }

}

void AppWindow::stop()
{
    m_status |= AppWindowStatus::NOT_RUNNING;
}

void AppWindow::destroy()
{
    if( (m_status & AppWindowStatus::NOT_CREATED ) != AppWindowStatus::NOT_CREATED ) // Checking if window was created.
    {
        m_status |= ( AppWindowStatus::NOT_RUNNING | AppWindowStatus::NOT_CREATED );

        SDL_DestroyRenderer(m_sdlRenderer); // Destroying SDL renderer.
        SDL_DestroyWindow(m_sdlWindow);     // Destroying SDL window.
    }
}

void AppWindow::show()
{
    if( isCreated() )
    {
        SDL_ShowWindow(m_sdlWindow);
    }
}

void AppWindow::hide()
{
    if( isCreated() )
    {
        SDL_HideWindow(m_sdlWindow);
    }
}

const AppWindow & AppWindow::operator = (const AppWindow &window)
{
    m_key                  = window.m_key;
    m_title                = window.m_title;
    m_x                    = window.m_x;
    m_y                    = window.m_y;
    m_width                = window.m_width;
    m_height               = window.m_height;
    m_eventsHandler        = window.m_eventsHandler;

    m_engine               = window.m_engine;
    m_sdlWindowInitFlags   = window.m_sdlWindowInitFlags;
    m_sdlRendererInitFlags = window.m_sdlRendererInitFlags;
    m_description          = window.m_description;

    ( !m_engine ) ?  m_status |=  AppWindowStatus::NO_ENGINE_POINTER
                  :  m_status &= ~AppWindowStatus::NO_ENGINE_POINTER;

    return *this;
}

bool AppWindow::operator == (const AppWindow &window) const
{
    bool equal = false;

    std::shared_ptr<EventsHandler> thisHandler    = m_eventsHandler.lock();
    std::shared_ptr<EventsHandler> anotherHandler = window.m_eventsHandler.lock();    

    if(  m_key                  == window.m_key
      && m_title                == window.m_title
      && m_x                    == window.m_x
      && m_y                    == window.m_y
      && m_width                == window.m_width
      && m_height               == window.m_height
      && thisHandler.get()      == anotherHandler.get()

      && m_engine               == window.m_engine
      && m_sdlWindowInitFlags   == window.m_sdlWindowInitFlags
      && m_sdlRendererInitFlags == window.m_sdlRendererInitFlags
      )
    {
        equal = true;
    }

    return equal;
}

bool AppWindow::operator != (const AppWindow &window) const
{
    return !(*this == window);
}

void AppWindow::setKey(const QString &key)
{
    m_key = key;
}

void AppWindow::setTitle(const QString &title)
{
    m_title = title;
    if( isCreated() )
    {
        QByteArray titleBytes = m_title.toUtf8();
        SDL_SetWindowTitle(m_sdlWindow, titleBytes.constData() );
    }
}

void AppWindow::setX(int x)
{
    m_x = x;
    if( isCreated() )
    {
        SDL_SetWindowPosition(m_sdlWindow, m_x, m_y);
    }
}

void AppWindow::setY(int y)
{
    m_y = y;
    if( isCreated() )
    {
        SDL_SetWindowPosition(m_sdlWindow, m_x, m_y);
    }
}

void AppWindow::setWidth(int width)
{
    m_width = width;
    if( isCreated() )
    {
        SDL_SetWindowSize(m_sdlWindow, m_width, m_height);
    }
}

void AppWindow::setHeight(int height)
{
    m_height = height;
    if( isCreated() )
    {
        SDL_SetWindowSize(m_sdlWindow, m_width, m_height);
    }
}

void AppWindow::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
    if( isCreated() )
    {
        SDL_SetWindowPosition(m_sdlWindow, m_x, m_y);
    }
}

void AppWindow::setSize(int width, int height)
{
    m_width  = width;
    m_height = height;
    if( isCreated() )
    {
        SDL_SetWindowSize(m_sdlWindow, m_width, m_height);
    }
}

void AppWindow::setEventsHandler(std::weak_ptr<EventsHandler> eventsHandler)
{
    m_eventsHandler = eventsHandler;
}

void AppWindow::setOpenGLContext(std::weak_ptr<OpenGLContext> openGLContext)
{
    m_openGLContext = openGLContext;
}

void AppWindow::setEngine(Engine *engine)
{
    m_engine = engine;

    ( !m_engine ) ?  m_status |=  AppWindowStatus::NO_ENGINE_POINTER
                  :  m_status &= ~AppWindowStatus::NO_ENGINE_POINTER;
}

void AppWindow::setSDLWindowInitFlags(Uint32 sdlWindowInitFlags)
{
    m_sdlWindowInitFlags = sdlWindowInitFlags;
}

void AppWindow::setSDLRendererInitFlags(Uint32 sdlRendererInitFlags)
{
    m_sdlRendererInitFlags = sdlRendererInitFlags;
}

void AppWindow::setDescription(const QString &description)
{
    m_description = description;
}

bool AppWindow::isCreated() const
{
    return (m_status & AppWindowStatus::NOT_CREATED) != AppWindowStatus::NOT_CREATED;
}

bool AppWindow::isRunning() const
{
    return (m_status & AppWindowStatus::NOT_RUNNING) != AppWindowStatus::NOT_RUNNING;
}

std::shared_ptr<AppWindow> AppWindow::createObject()
{
    return std::make_shared<AppWindow>();
}

AppWindow::AppWindow( const AppWindow &window ) :
    m_key                  ( window.m_key                  ),
    m_title                ( window.m_title                ),
    m_x                    ( window.m_x                    ),
    m_y                    ( window.m_y                    ),
    m_width                ( window.m_width                ),
    m_height               ( window.m_height               ),
    m_sdlWindow            ( window.m_sdlWindow            ),
    m_sdlRenderer          ( window.m_sdlRenderer          ),
    m_eventsHandler        ( window.m_eventsHandler        ),
    m_openGLContext        ( window.m_openGLContext        ),
    m_engine               ( window.m_engine               ),
    m_sdlWindowInitFlags   ( window.m_sdlWindowInitFlags   ),
    m_sdlRendererInitFlags ( window.m_sdlRendererInitFlags ),
    m_description          ( window.m_description          ),
    m_name                 ( window.m_name                 ),
    m_status               ( window.m_status               )
{
}
