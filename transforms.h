#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "commonincludings.h"

//! Holds object transformations in 3D space.
class Transforms
{
public:
    Transforms();                                                        //! Default constructor.
    Transforms( const QVector3D &translation );                          //! Parameterized constructor.
    Transforms( GLfloat translationX                                     //! Parameterized constructor.
              , GLfloat translationY
              , GLfloat translationZ
              );
    Transforms( const QVector3D &translation                             //! Parameterized constructor.
              , const QVector4D &rotation
              );
    Transforms( GLfloat translationX                                     //! Parameterized constructor.
              , GLfloat translationY
              , GLfloat translationZ
              , GLfloat rotationAngle
              , GLfloat rotationX
              , GLfloat rotationY
              , GLfloat rotationZ
              );
    Transforms( const QVector3D &translation                             //! Parameterized constructor.
              , const QVector4D &rotation
              , const QVector3D &scaling
              );
    Transforms( GLfloat translationX                                     //! Parameterized constructor.
              , GLfloat translationY
              , GLfloat translationZ
              , GLfloat rotationAngle
              , GLfloat rotationX
              , GLfloat rotationY
              , GLfloat rotationZ
              , GLfloat scalingX
              , GLfloat scalingY
              , GLfloat scalingZ
              );

    Transforms( const Transforms &transforms );                          //! Copying constructor.

    virtual ~Transforms() {}

    const Transforms & operator = (const Transforms &transforms);        //! Operator " =  ".
    bool  operator == (const Transforms &transforms) const;              //! Operator " == ".
    bool  operator != (const Transforms &transforms) const;              //! Operator " != ".

public:
    const QVector3D & getTranslation() const { return m_translation; }   //! Returns object translation transformation.
    QVector3D & getTranslation() { return m_translation; }               //! Returns object translation transformation, overloaded function.
    void setTranslation(const QVector3D &translation);                   //! Sets object translation transformation.
    void setTranslation(GLfloat x, GLfloat y, GLfloat z);                //! Sets object translation transformation, overloaded function.

    const QVector4D & getRotation() const { return m_rotation; }         //! Returns object rotation transformation.
    QVector4D & getRotation() { return m_rotation; }                     //! Returns object rotation transformation, overloaded function.
    void setRotation(const QVector4D &rotation);                         //! Sets object rotation transformation.
    void setRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);    //! Sets object rotation transformation, overloaded function.

    const QVector3D & getScaling() const { return m_scaling; }           //! Returns object scaling transformation.
    QVector3D & getScaling() { return m_scaling; }                       //! Returns object scaling transformation, overloaded function.
    void setScaling(const QVector3D &scaling);                           //! Sets object scaling transformation.
    void setScaling(GLfloat x, GLfloat y, GLfloat z);                    //! Sets object scaling transformation, overloaded function.

    const QMatrix4x4 & getModel() const { return m_model; }              //! Returns Model matrix used for object positioning in 3D space.

protected:
    virtual const QMatrix4x4 & calculateModel(); //! Calculates Model matrix and returns it.

    void setModel(const QMatrix4x4 &model);      //! Sets Model matrix.

private:
    QVector3D       m_translation;  //! Object translation transformation.
    QVector4D       m_rotation;     //! Object rotation transformation.
    QVector3D       m_scaling;      //! Object scaling transformation.

    QMatrix4x4      m_model;        //! Model matrix used for object positioning in 3D space.
};

#endif // TRANSFORMS_H
