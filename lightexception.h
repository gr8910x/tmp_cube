#ifndef LIGHTEXCEPTION_H
#define LIGHTEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Light;

//! Implements exceptionslinked with light objects.
class LightException : public CommonException
{
public:
    LightException() noexcept;                                 //! Default constructor.
    LightException( const QString &message ) noexcept;         //! Parameterized constructor.
    LightException( Light         *light   ) noexcept;         //! Parameterized constructor.
    LightException( Light         *light                       //! Parameterized constructor.
                  , const QString &message ) noexcept;

    LightException( const LightException &exception ) noexcept;//! Copying constructor.

    virtual ~LightException() {}

    const LightException & operator = (const LightException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const LightException &exception) const noexcept;          //! Operator " == ".
    bool  operator != (const LightException &exception) const noexcept;          //! Operator " != ".

public:
    const Light * getLight() const noexcept { return m_light; }//! Returns pointer to light object where exception occured.
    Light * getLight() noexcept { return m_light; }            //! Returns pointer to light object where exception occured, overloaded function.
    void setLight(Light *light) noexcept;                      //! Sets pointer to light object where exception occured, overloaded function.

public:
    static uint getCounter() { return counter; }    //! Returns number of created light exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override; //! Fills info bytes array with bytes and returns it.

private:
    static uint counter;  //! Counter of created light exception objects.

private:
    Light *   m_light;    //! A pointer to light object where exception occured.
};


#endif // LIGHTEXCEPTION_H
