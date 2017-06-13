#include "eventshandler.h"
#include "appwindow.h"

uint EventsHandler::counter = 0;

EventsHandler::EventsHandler() :
    m_sdlEvent    ( SDL_Event()         ),
    m_description ( "Empty description" )
{
    m_name = ++ EventsHandler::counter;
}

EventsHandler::EventsHandler( const QString &description ) :
    m_sdlEvent    ( SDL_Event()         ),
    m_description ( description         )
{
    m_name = ++ EventsHandler::counter;
}

void EventsHandler::handle(AppWindow *window)
{
    while( SDL_PollEvent(&m_sdlEvent) )         // Beginning handling SDL events.
    {
        switch( m_sdlEvent.type )
        {
        case SDL_QUIT:                          // Window closing event.
            window->stop();                     // Stopping window.
            break;
        case SDL_KEYDOWN:                       // Key pressing event.
            switch( m_sdlEvent.key.keysym.sym )
            {
            case SDLK_ESCAPE:                       // ESC key is pressed.
                window->stop();                     // Stopping window.
                break;
            }
            break;
        }
    }
}

const EventsHandler & EventsHandler::operator = (const EventsHandler &handler)
{
    m_sdlEvent     = handler.m_sdlEvent;
    m_description  = handler.m_description;

    return *this;
}

void EventsHandler::setDescription(const QString &description)
{
    m_description = description;
}

std::shared_ptr<EventsHandler> EventsHandler::createObject()
{
    return std::make_shared<EventsHandler>();
}

EventsHandler::EventsHandler( const EventsHandler &handler ) :
    m_sdlEvent    ( handler.m_sdlEvent    ),
    m_name        ( handler.m_name        ),
    m_description ( handler.m_description )
{
}
