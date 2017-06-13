#include "vertex.h"

GLuint64 Vertex::counter = 0;

Vertex::Vertex() :
    m_coordinates (                        ),
    m_color       ( 0.0f, 0.0f, 0.0f, 1.0f ),
    m_normal      (                        )
{
    ++ Vertex::counter;
}

Vertex::Vertex( const QVector3D &coordinates ) :
    m_coordinates ( coordinates            ),
    m_color       ( 0.0f, 0.0f, 0.0f, 1.0f ),
    m_normal      (                        )
{
    ++ Vertex::counter;
}

Vertex::Vertex( const QVector3D &coordinates
              , const QVector4D &color
              ) :
    m_coordinates ( coordinates   ),
    m_color       ( color         ),
    m_normal      (               )
{
    ++ Vertex::counter;
}

Vertex::Vertex( const QVector3D &coordinates
              , const QVector4D &color
              , const QVector3D &normal
              ) :
    m_coordinates ( coordinates   ),
    m_color       ( color         ),
    m_normal      ( normal        )
{
    ++ Vertex::counter;
}

Vertex::Vertex(const Vertex &vertex) :
    m_coordinates ( vertex.m_coordinates ),
    m_color       ( vertex.m_color       ),
    m_normal      ( vertex.m_normal      )
{    
}

const Vertex & Vertex::operator = (const Vertex &vertex)
{
    m_coordinates   = vertex.m_coordinates;
    m_color         = vertex.m_color;
    m_normal        = vertex.m_normal;

    return *this;
}

bool Vertex::operator == (const Vertex &vertex) const
{
    bool equal = false;

    if(  m_coordinates == vertex.m_coordinates
      && m_color       == vertex.m_color
      && m_normal      == vertex.m_normal )
    {
        equal = true;
    }

    return equal;
}

bool Vertex::operator !=(const Vertex &vertex) const
{
    return !(*this == vertex);
}

void Vertex::setCoordinates(const QVector3D &coordinates)
{
    m_coordinates = coordinates;
}

void Vertex::setCoordinates(GLfloat x, GLfloat y, GLfloat z)
{
    m_coordinates.setX(x);
    m_coordinates.setY(y);
    m_coordinates.setZ(z);
}

void Vertex::setColor(const QVector4D &color)
{
    m_color = color;
}

void Vertex::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_color.setX(r);
    m_color.setY(g);
    m_color.setZ(b);
    m_color.setW(a);
}

void Vertex::setNormal(const QVector3D &normal)
{
    m_normal = normal;
}

void Vertex::setNormal(GLfloat x, GLfloat y, GLfloat z)
{
    m_normal.setX(x);
    m_normal.setY(y);
    m_normal.setZ(z);
}
