#ifndef APPWINDOWEXCEPTION_H
#define APPWINDOWEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class AppWindow;

class AppWindowException : public CommonException
{
public:
    AppWindowException() noexcept;                            //! Default constructor.
    AppWindowException( const QString &message ) noexcept;    //! Parameterized constructor.
    AppWindowException( AppWindow     *window  ) noexcept;    //! Parameterized constructor.
    AppWindowException( AppWindow     *window                 //! Parameterized constructor.
                      , const QString &message ) noexcept;
    AppWindowException( AppWindow     *window                 //! Parameterized constructor.
                      , const QString &message
                      , const QString &sdlErrorInfo ) noexcept;

    AppWindowException( const AppWindowException &exception ) noexcept;//! Copying constructor.

    virtual ~AppWindowException() {}

    const AppWindowException & operator = (const AppWindowException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const AppWindowException &exception) const noexcept;              //! Operator " == ".
    bool  operator != (const AppWindowException &exception) const noexcept;              //! Operator " != ".

public:
    const AppWindow * getWindow() const noexcept { return m_window; }//! Returns pointer to application window object where exception occurred.
    AppWindow * getWindow() noexcept { return m_window; }            //! Returns pointer to application window object where exception occurred, overloaded function.
    void setWindow(AppWindow * window) noexcept;                     //! Sets pointer to application window object where exception occurred.

    const QString & getSDLErrorInfo() const noexcept { return m_sdlErrorInfo; }//! Returns SDL window error info.
    void setSDLErrorInfo(const QString &errorInfo) noexcept;                   //! Sets SDL window error info.

public:
    static uint getCounter() { return counter; }          //! Returns number of created application window exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;//! Fills info bytes array with bytes and returns it.

private:
    static uint counter;           //! Counter of created application window exception objects.

private:
    AppWindow *     m_window;      //! A pointer to application window object where exception occurred.

    QString         m_sdlErrorInfo;//! SDL window error info.
};

#endif // APPWINDOWEXCEPTION_H
