#include "transforms.h"

Transforms::Transforms() :
    m_translation (                  ),
    m_rotation    (                  ),
    m_scaling     ( 1.0f, 1.0f, 1.0f ),
    m_model       (                  )
{
    calculateModel();
}

Transforms::Transforms( const QVector3D &translation ) :
    m_translation ( translation      ),
    m_rotation    (                  ),
    m_scaling     ( 1.0f, 1.0f, 1.0f ),
    m_model       (                  )
{
    calculateModel();
}

Transforms::Transforms( GLfloat translationX
                      , GLfloat translationY
                      , GLfloat translationZ
                      ) :
    m_translation ( translationX, translationY, translationZ ),
    m_rotation    (                                          ),
    m_scaling     ( 1.0f,         1.0f,         1.0f         ),
    m_model       (                                          )
{
    calculateModel();
}

Transforms::Transforms( const QVector3D &translation
                      , const QVector4D &rotation
                      ) :
    m_translation ( translation      ),
    m_rotation    ( rotation         ),
    m_scaling     ( 1.0f, 1.0f, 1.0f ),
    m_model       (                  )
{
    calculateModel();
}

Transforms::Transforms( GLfloat translationX
                      , GLfloat translationY
                      , GLfloat translationZ
                      , GLfloat rotationAngle
                      , GLfloat rotationX
                      , GLfloat rotationY
                      , GLfloat rotationZ
                      ) :
    m_translation ( translationX,  translationY, translationZ            ),
    m_rotation    ( rotationAngle, rotationX,    rotationY,    rotationZ ),
    m_scaling     ( 1.0f,          1.0f,         1.0f                    ),
    m_model       (                                                      )
{
    calculateModel();
}

Transforms::Transforms( const QVector3D &translation
                      , const QVector4D &rotation
                      , const QVector3D &scaling
                      ) :
    m_translation ( translation ),
    m_rotation    ( rotation    ),
    m_scaling     ( scaling     ),
    m_model       (             )
{
    calculateModel();
}

Transforms::Transforms( GLfloat translationX
                      , GLfloat translationY
                      , GLfloat translationZ
                      , GLfloat rotationAngle
                      , GLfloat rotationX
                      , GLfloat rotationY
                      , GLfloat rotationZ
                      , GLfloat scalingX
                      , GLfloat scalingY
                      , GLfloat scalingZ
                      ) :
    m_translation ( translationX,  translationY, translationZ           ),
    m_rotation    ( rotationAngle, rotationX,    rotationY,   rotationZ ),
    m_scaling     ( scalingX,      scalingY,     scalingZ               ),
    m_model       (                                                     )
{
    calculateModel();
}

Transforms::Transforms( const Transforms &transforms ) :
    m_translation ( transforms.m_translation ),
    m_rotation    ( transforms.m_rotation    ),
    m_scaling     ( transforms.m_scaling     ),
    m_model       ( transforms.m_model       )
{
}

const Transforms & Transforms::operator = (const Transforms &transforms)
{
    m_translation = transforms.m_translation;
    m_rotation    = transforms.m_rotation;
    m_scaling     = transforms.m_scaling;
    m_model       = transforms.m_model;

    return *this;
}

bool Transforms::operator == (const Transforms &transforms) const
{
    bool equal = false;
    if(  m_translation == transforms.m_translation
      && m_rotation    == transforms.m_rotation
      && m_scaling     == transforms.m_scaling
      && m_model       == transforms.m_model
      )
    {
        equal = true;
    }

    return equal;
}

bool Transforms::operator != (const Transforms &transforms) const
{
    return !(*this == transforms);
}

void Transforms::setTranslation(const QVector3D &translation)
{
    m_translation = translation;
    calculateModel();
}

void Transforms::setRotation(const QVector4D &rotation)
{
    m_rotation = rotation;
    calculateModel();
}

void Transforms::setScaling(const QVector3D &scaling)
{
    m_scaling = scaling;
    calculateModel();
}

void Transforms::setTranslation(GLfloat x, GLfloat y, GLfloat z)
{
    m_translation.setX(x);
    m_translation.setY(y);
    m_translation.setZ(z);
    calculateModel();
}

void Transforms::setRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    m_rotation.setX(angle);
    m_rotation.setY(x);
    m_rotation.setZ(y);
    m_rotation.setW(z);
    calculateModel();
}

void Transforms::setScaling(GLfloat x, GLfloat y, GLfloat z)
{
    m_scaling.setX(x);
    m_scaling.setY(y);
    m_scaling.setZ(z);
    calculateModel();
}

const QMatrix4x4 & Transforms::calculateModel()
{
    m_model.setToIdentity();         // Settintg model matrix to identity.

    m_model.translate(m_translation);// Setting translation.
    m_model.rotate(m_rotation.x(), m_rotation.y(), m_rotation.z(), m_rotation.w() );// Setting rotation.
    m_model.scale(m_scaling);        // Setting scaling.

    return m_model;
}

void Transforms::setModel(const QMatrix4x4 &model)
{
    m_model = model;
}
