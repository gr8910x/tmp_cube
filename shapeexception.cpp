#include "shapeexception.h"
#include "shape.h"

using namespace com_defs;

uint ShapeException::counter = 0;

ShapeException::ShapeException() noexcept :
    CommonException  (         ),
    m_shape          ( nullptr )
{
    ++ ShapeException::counter;
    fillInfoBytes();
}

ShapeException::ShapeException( const QString &message ) noexcept :
    CommonException  ( message ),
    m_shape          ( nullptr )

{
    ++ ShapeException::counter;
    fillInfoBytes();
}

ShapeException::ShapeException( Shape *shape ) noexcept :
    CommonException  (         ),
    m_shape          ( shape   )
{
    ++ ShapeException::counter;
    fillInfoBytes();
}

ShapeException::ShapeException( Shape         *shape
                              , const QString &message ) noexcept :
    CommonException  ( message ),
    m_shape          ( shape   )
{
    ++ ShapeException::counter;
    fillInfoBytes();
}

ShapeException::ShapeException( const ShapeException &exception ) noexcept :
    CommonException  ( exception         ),
    m_shape          ( exception.m_shape )
{
}

const ShapeException & ShapeException::operator = (const ShapeException &exception) noexcept
{
    CommonException::operator = (exception);
    m_shape                   = exception.m_shape;

    return *this;
}

bool ShapeException::operator == (const ShapeException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_shape                   == exception.m_shape )
    {
        equal = true;
    }

    return equal;
}

bool ShapeException::operator != (const ShapeException &exception) const noexcept
{
    return !(*this == exception);
}

void ShapeException::setShape(Shape *shape) noexcept
{
    m_shape = shape;
}

const QByteArray & ShapeException::fillInfoBytes() noexcept
{    
    QString infoString = getMessage();
    if( m_shape )
    {
        uint status = m_shape->getStatus();
        infoString  += QString("\n Shape name: \t %1").arg(m_shape->getName() )
                    +  QString("\n Shape description: %1").arg(m_shape->getDescription() );
        if( (status & ShapeStatus::INVALID_BUFFERS) == ShapeStatus::INVALID_BUFFERS )
        {            
            infoString += QString("\n Mesh buffers were invalid \t %1").arg(NUM_OF_SHAPE_DRAW_ATTEMPTS)
                       +  QString("\t times while trying to draw a shape.");
        }
        if( (status & ShapeStatus::NO_PROGRAM) == ShapeStatus::NO_PROGRAM )
        {
            infoString += QString("\n Shape shading program not set.");
        }
    }
    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
