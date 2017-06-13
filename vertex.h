#ifndef VERTEX_H
#define VERTEX_H

#include "commonincludings.h"

//! Implements OpenGL 3D-space vertex.
class Vertex
{
public:
    Vertex();                                                         //! Default constructor.
    Vertex( const QVector3D &coordinates );                           //! Parameterized constructor.
    Vertex( const QVector3D &coordinates                              //! Parameterized constructor.
          , const QVector4D &color
          );
    Vertex( const QVector3D &coordinates                              //! Parameterized constructor.
          , const QVector4D &color
          , const QVector3D &normal
          );

    Vertex( const Vertex &vertex );                                   //! Copying constructor.

    virtual ~Vertex() {}

    const Vertex & operator = (const Vertex &vertex);                 //! Operator " =  ".
    bool  operator == (const Vertex &vertex) const;                   //! Operator " == ".
    bool  operator != (const Vertex &vertex) const;                   //! Operator " != ".

public:
    const QVector3D & getCoordinates() const { return m_coordinates; }//! Returns coordinates of vertex.
    QVector3D & getCoordinates() { return m_coordinates; }            //! Returns coordinates of vertex, overloaded function.
    void setCoordinates(const QVector3D &coordinates);                //! Sets coordinates of vertex.
    void setCoordinates(GLfloat x, GLfloat y, GLfloat z);             //! Sets coordinates of vertex, overloaded function.

    const QVector4D & getColor() const { return m_color; }            //! Returns color of vertex.
    QVector4D & getColor() {return m_color; }                         //! Returns color of vertex, overloaded function.
    void setColor(const QVector4D &color);                            //! Sets color of vertex.
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);        //! Sets color of vertex, overloaded function.

    const QVector3D & getNormal() const { return m_normal; }          //! Returns normal of vertex.
    QVector3D & getNormal() { return m_normal; }                      //! Returns normal of vertex, overloaded function.
    void setNormal(const QVector3D &normal);                          //! Sets normal of vertex.
    void setNormal(GLfloat x, GLfloat y, GLfloat z);                  //! Sets normal of vertex, overloaded function.    

public:
    static GLuint64 getCounter() { return counter; }                  //! Returns number of created vertices.

private:
    static GLuint64 counter;            //! Counter of created vertices.

private:
    QVector3D   m_coordinates;          //! Coordinates of vertex.
    QVector4D   m_color;                //! Color of vertex.
    QVector3D   m_normal;               //! Normal of vertex.    

};

#endif // VERTEX_H
