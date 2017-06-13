#ifndef IAPPWINDOW_H
#define IAPPWINDOW_H

//! Interface for application window implementation.
class IAppWindow
{
public:
    virtual void create() noexcept(false) = 0;  //! Creates application window.
    virtual void run() noexcept(false) = 0;     //! Runs application window.
    virtual void stop() = 0;                    //! Stops application window.
    virtual void destroy() = 0;                 //! Destroys application window.
    virtual void show() = 0;                    //! Shows application window.
    virtual void hide() = 0;                    //! Hides application window.

    virtual ~IAppWindow() {}
};

#endif // IAPPWINDOW_H
