#ifndef ENGINEEXCEPTION_H
#define ENGINEEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Engine;

class EngineException : public CommonException
{
public:
    EngineException() noexcept;                                   //! Default constructor.
    EngineException( const QString &message ) noexcept;           //! Parameterized constructor.
    EngineException( Engine        *engine ) noexcept;            //! Parameterized constructor.
    EngineException( Engine        *engine                        //! Parameterized constructor.
                   , const QString &message
                   , const QString &sdlErrorInfo = ""
                   ) noexcept;

    EngineException( const EngineException &exception ) noexcept; //! Copying constructor.

    virtual ~EngineException() {}

    const EngineException & operator = (const EngineException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const EngineException &exception) const noexcept;           //! Operator " == ".
    bool  operator != (const EngineException &exception) const noexcept;           //! Operator " != ".

public:
    const Engine * getEngine() const noexcept { return m_engine; }//! Returns pointer to engine object where exception occured.
    Engine * getEngine() noexcept { return m_engine; }            //! Returns pointer to engine object where exception occured, overloaded function.
    void setEngine(Engine *engine) noexcept;                      //! Sets pointer to engine object where exception occured.

    const QString & getSDLErrorInfo() const noexcept { return m_sdlErrorInfo; }//! Returns SDL library error info.
    void setSDLErrorInfo(const QString &sdlErrorInfo) noexcept;                //! Sets SDL library error info.

public:
    static uint getCounter() { return counter; }                  //! Returns number of created engine exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;//! Fills info bytes array with bytes and returns it.

private:
    static uint counter;           //! Counter of created engine exception objects.

private:
    Engine *        m_engine;      //! Pointer to engine object where exception occured.

    QString         m_sdlErrorInfo;//! SDL library error info.
};

#endif // ENGINEEXCEPTION_H
