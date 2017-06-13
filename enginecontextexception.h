#ifndef ENGINECONTEXTEXCEPTION_H
#define ENGINECONTEXTEXCEPTION_H

#include "commonexception.h"

class EngineContext;

class EngineContextException : public CommonException
{
public:
    EngineContextException() noexcept;                                           //! Default constructor.
    EngineContextException( EngineContext *context ) noexcept;                   //! Parameterized constructor.
    EngineContextException( const QString &message ) noexcept;                   //! Parameterized constructor.
    EngineContextException( EngineContext *context                               //! Parameterized constructor.
                          , const QString &message ) noexcept;

    EngineContextException( const EngineContextException &exception ) noexcept;  //! Copying constructor.

    virtual ~EngineContextException() {}

    const EngineContextException & operator = (const EngineContextException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const EngineContextException &exception) const noexcept;                  //! Operator " == ".
    bool  operator != (const EngineContextException &exception) const noexcept;                  //! Operator " != ".

public:
    const EngineContext * getEngineContext() const noexcept { return m_context; }//! Returns pointer to engine context object where exception occured.
    EngineContext * getEngineContext() noexcept { return m_context; }            //! Returns pointer to engine context object where exception occured, overloaded function.
    void setEngineContext(EngineContext *context) noexcept;                      //! Sets pointer to engine context object where exception occured.

public:
    static uint getCounter() { return counter; }        //! Returns number of created engine context exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;//! Fills info bytes array with bytes and returns it.

private:
    static uint counter;

private:
    EngineContext *      m_context;     //! Pointer to engine context object where exception occured.
};

#endif // ENGINECONTEXTEXCEPTION_H
