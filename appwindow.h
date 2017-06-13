#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "commonincludings.h"
#include "iappwindow.h"

class EventsHandler;
class OpenGLContext;
class Engine;

//! Implements application window class.
class AppWindow : public IAppWindow
{
public:
    AppWindow();                                             //! Default constructor.
    AppWindow( const QString &title );                       //! Parameterized constructor.
    AppWindow( int            width                          //! Parameterized constructor.
             , int            height
             );
    AppWindow( int            x                              //! Parameterized constructor.
             , int            y
             , int            width
             , int            height
             );
    AppWindow( const QString &title                          //! Parameterized constructor.
             , int            x
             , int            y
             , int            width
             , int            height
             );
    AppWindow( const QString &title                          //! Parameterized constructor.
             , int            x
             , int            y
             , int            width
             , int            height
             , std::weak_ptr<EventsHandler> eventsHandler
             );
    AppWindow( const QString &title                          //! Parameterized constructor.
             , int            x
             , int            y
             , int            width
             , int            height
             , Engine        *engine
             , std::weak_ptr<EventsHandler> eventsHandler
             , const QString &description
             );
    AppWindow( const QString &title                          //! Parameterized constructor.
             , int            x
             , int            y
             , int            width
             , int            height
             , std::weak_ptr<EventsHandler> eventsHandler
             , Uint32         sdlWindowInitFlags
             , const QString &description
             );
    AppWindow( const QString &key                            //! Parameterized constructor.
             , const QString &title
             , int            x
             , int            y
             , int            width
             , int            height
             , Engine        *engine
             , std::weak_ptr<EventsHandler> eventsHandler
             , Uint32         sdlWindowInitFlags
             , Uint32         sdlRendererInitFlags
             , const QString &description
             );

    virtual ~AppWindow();

    virtual void create() noexcept(false) override;          //! Creates application window.
    virtual void run() noexcept(false) override;             //! Runs application window.
    virtual void stop() override;                            //! Stops application window.
    virtual void destroy() override;                         //! Destroys application window.
    virtual void show() override;                            //! Shows application window.
    virtual void hide() override;                            //! Hides application window.

    const AppWindow & operator = (const AppWindow &window);  //! Operator " =  ".
    bool  operator == (const AppWindow &window) const;       //! Operator " == ".
    bool  operator != (const AppWindow &window) const;       //! Operator " != ".

public:
    const QString & getKey() const { return m_key; }         //! Returns window key.
    void  setKey(const QString & key);                       //! Sets window key.

    const QString & getTitle() const { return m_title; }     //! Returns window title.
    void setTitle(const QString &title);                     //! Sets window title.

    int  getX() const { return m_x; }                        //! Returns x position of the window.
    int  getY() const { return m_y; }                        //! Returns y position of the window.
    int  getWidth() const { return m_width; }                //! Returns window width.
    int  getHeight() const { return m_height; }              //! Returns window height.
    void setX(int x);                                        //! Sets x position of the window.
    void setY(int y);                                        //! Sets y position of the window.
    void setWidth(int width);                                //! Sets window width.
    void setHeight(int height);                              //! Sets window height.

    void setPosition(int x, int y);                          //! Sets window position.
    void setSize(int width, int height);                     //! Sets window size.

    const SDL_Window * getSDLWindow() const { return m_sdlWindow; }      //! Returns pointer to SDL window.
    const SDL_Renderer * getSDLRenderer() const { return m_sdlRenderer; }//! Returns pointer to SDL window renderer.
    SDL_Window * getSDLWindow() { return m_sdlWindow; }                  //! Returns pointer to SDL window, overloaded function.
    SDL_Renderer * getSDLRenderer() { return m_sdlRenderer; }            //! Returns pointer to SDL window renderer, overloaded function.

    std::weak_ptr<EventsHandler> getEventsHandler() { return m_eventsHandler; }//! Returns events handler pointer.
    void setEventsHandler(std::weak_ptr<EventsHandler> eventsHandler);         //! Sets events handler pointer.

    std::weak_ptr<OpenGLContext> getOpenGLContext() { return m_openGLContext; }//! Returns OpenGL context pointer.
    void setOpenGLContext(std::weak_ptr<OpenGLContext> openGLContext);         //! Sets OpenGL context pointer.

    const Engine * getEngine() const { return m_engine; }                //! Returns pointer to engine object.
    Engine * getEngine() { return m_engine; }                            //! Returns pointer to engine object, overloaded function.
    void setEngine(Engine *engine);                                      //! Sets pointer to engine object.

    Uint32 getSDLWindowInitFlags() const { return m_sdlWindowInitFlags; }      //! Returns SDL window initialization flags bitmask.
    Uint32 getSDLRendererInitFlags() const { return m_sdlRendererInitFlags; }  //! Returns SDL renderer initialization flags bitmask.
    void setSDLWindowInitFlags(Uint32 sdlWindowInitFlags);                     //! Sets SDL window initialization flags bitmask
    void setSDLRendererInitFlags(Uint32 sdlRendererInitFlags);                 //! Sets SDL renderer initialization flags bitmask.

    const QString & getDescription() const { return m_description; }           //! Returns window description.
    void setDescription(const QString &description);                           //! Sets window description.

    uint getName() const { return m_name; }                  //! Returns autogenerated window name.
    uint getStatus() const { return m_status; }              //! Returns window object status bitmask.

    bool isCreated() const;                                  //! Returns true if window was created.
    bool isRunning() const;                                  //! Returns true if window is running.

public:
    static uint getCounter() { return counter; }             //! Returns number of created window objects.

    static std::shared_ptr<AppWindow> createObject();        //! Creates new window and returns pointer to it.

protected:
    AppWindow( const AppWindow &window );                    //! Copying constructor.

    void setStatus(uint status) { m_status = status; }       //! Sets window object status bitmask.

private:
    static uint counter;                //! Counter of created window objects.

private:
    QString          m_key;             //! Window key.
    QString          m_title;           //! Window title.

    int              m_x;               //! X position of the window, SDL_WINDOWPOS_UNDEFINED by default.
    int              m_y;               //! Y position of the window, SDL_WINDOWPOS_UNDEFINED by default.
    int              m_width;           //! Window width, 640 by default.
    int              m_height;          //! Window height, 480 by default.

    SDL_Window *     m_sdlWindow;       //! SDL window pointer.
    SDL_Renderer *   m_sdlRenderer;     //! SDL window renderer pointer.

    std::weak_ptr<EventsHandler>  m_eventsHandler;//! Events handler pointer.
    std::weak_ptr<OpenGLContext>  m_openGLContext;//! OpenGL context pointer.

    Engine *         m_engine;          //! Pointer to engine object.

    Uint32           m_sdlWindowInitFlags;  //! SDL window initialization flags bitmask, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL by default.
    Uint32           m_sdlRendererInitFlags;//! SDL renderer initialization flags bitmask, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC by default.

    QString          m_description;     //! Window description.

    uint             m_name;            //! Autogenerated window name.
    uint             m_status;          //! Window object status bitmask.

};

#endif // APPWINDOW_H
