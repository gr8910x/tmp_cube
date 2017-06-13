#include "engine.h"
#include "engineexception.h"

using namespace com_defs;

uint Engine::counter = 0;

Engine::Engine() :
    m_context       ( this                     ),
    m_sdlInitFlags  ( SDL_INIT_EVERYTHING      ),
    m_status        ( EngineStatus::NOT_INITED ),
    m_tasksManager  (                          ),
    m_description   ( "Empty description"      )
{
    m_name = ++ Engine::counter;
}

Engine::Engine( const QString &engineDescription
              , Uint32         sdlInitFlags
              , const QString &engineContextDescription
              , const QString &engineTasksManagerDescription
              ) :
    m_context        ( this, engineContextDescription  ),
    m_sdlInitFlags   ( sdlInitFlags                    ),
    m_status         ( EngineStatus::NOT_INITED        ),
    m_tasksManager   ( engineTasksManagerDescription   ),
    m_description    ( engineDescription               )
{
    m_name = ++ Engine::counter;
}

Engine::~Engine()
{
    close();
}

void Engine::init() noexcept(false)
{
    if( !isInited() )
    {
        int success = SDL_Init(m_sdlInitFlags);
        ( success < 0 ) ? m_status |=  EngineStatus::NOT_INITED
                        : m_status &= ~EngineStatus::NOT_INITED;
        if( (m_status & EngineStatus::NOT_INITED) == EngineStatus::NOT_INITED )
        {
            QString sdlError(SDL_GetError() );
            throw EngineException(this, "Engine exception occured", sdlError);
        }
    }
}

void Engine::close()
{
    if( isInited() )
    {
        m_tasksManager.receiveAll();  // Waiting and receiving tasks results and exceptions.

        m_context.removeAll();
        SDL_Quit();
        m_status |= EngineStatus::NOT_INITED;
    }
}

const Engine & Engine::operator = (const Engine &engine)
{
    m_context        = engine.m_context;
    m_sdlInitFlags   = engine.m_sdlInitFlags;

    m_description    = engine.m_description;

    return *this;
}

void Engine::setSDLInitFlags(Uint32 sdlInitFlags)
{
    m_sdlInitFlags = sdlInitFlags;
}

void Engine::setDescription(const QString &description)
{
    m_description = description;
}

bool Engine::isInited() const
{
    return (m_status & EngineStatus::NOT_INITED) != EngineStatus::NOT_INITED;
}

