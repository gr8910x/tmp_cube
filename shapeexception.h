#ifndef SHAPEEXCEPTION_H
#define SHAPEEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Shape;

//! Implements exceptions linked with OpenGL shape objects.
class ShapeException : public CommonException
{
public:
    ShapeException() noexcept;                                     //! Default constructor.
    ShapeException( const QString &message ) noexcept;             //! Parameterized constructor.
    ShapeException( Shape         *shape   ) noexcept;             //! Parameterized constructor.
    ShapeException( Shape         *shape                           //! Parameterized constructor.
                  , const QString &message ) noexcept;

    ShapeException( const ShapeException &exception) noexcept;     //! Copying constructor.

    virtual ~ShapeException() {}

    const ShapeException & operator = (const ShapeException &exception) noexcept;//! Operator " =  ".
    bool  operator == (const ShapeException &exception) const noexcept;          //! Operator " == ".
    bool  operator != (const ShapeException &exception) const noexcept;          //! Operator " != ".

public:
    const Shape * getShape() const noexcept { return m_shape; }    //! Returns pointer to shape where exception occured.
    Shape * getShape() noexcept { return m_shape; }                //! Returns pointer to shape where exception occured, overloaded function.
    void setShape(Shape *shape) noexcept;                          //! Sets pointer to shape where exception occured.

public:
    static uint getCounter() { return counter; }                   //! Returns number of created shape exception objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;  //! Fills info bytes array with bytes and returns it.

private:
    static uint counter;    //! Counter of created shape exception objects.

private:
    Shape *        m_shape; //! A pointer to shape where exception occured.
};

#endif // SHAPEEXCEPTION_H
