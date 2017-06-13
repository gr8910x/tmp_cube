#ifndef PROGRAMEXCEPTION_H
#define PROGRAMEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Program;

//! Implements exception linked with OpenGL shader program.
class ProgramException : public CommonException
{
public:
    ProgramException() noexcept;                                                     //! Default constructor.
    ProgramException( const QString &message ) noexcept;                             //! Parameterized constructor.
    ProgramException( Program       *program ) noexcept;                             //! Parameterized constructor.
    ProgramException( Program       *program                                         //! Parameterized constructor.
                    , const QString &message ) noexcept;
    ProgramException( Program       *program                                         //! Parameterized constructor.
                    , const QString &message
                    , const QString &linkingLog ) noexcept;

    ProgramException( const ProgramException &exception ) noexcept;                  //! Copying constructor.

    virtual ~ProgramException() {}

    const ProgramException & operator = (const ProgramException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const ProgramException &exception) const noexcept;            //! Operator " == ".
    bool  operator != (const ProgramException &exception) const noexcept;            //! Operator " != ".

public:
    const Program * getProgram() const noexcept { return m_program; }                //! Returns pointer to object where exception occured.
    Program * getProgram() noexcept { return m_program; }                            //! Returns pointer to object where exception occured, overloaded function.
    void setProgram(Program *program) noexcept;                                      //! Sets pointer to object where exception occured.

    const QString & getLinkingLog() const noexcept { return m_linkingLog; }          //! Returns program linking log.
    void setLinkingLog(const QString & linkingLog) noexcept;                         //! Sets program linking log.

public:
    static uint getCounter() { return counter; }                                     //! Returns number of creted OpenGL program exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;                    //! Fills info bytes array with bytes and returns it.

private:
    static uint  counter;           //! Counter of created OpenGL program exception objects.

private:
    Program *       m_program;      //! A pointer to program object where exception occured.

    QString         m_linkingLog;   //! Program OpneGL linking log.
};

#endif // PROGRAMEXCEPTION_H
