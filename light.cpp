#include "light.h"

using namespace com_defs;

GLuint Light::counter = 0;

Light::Light() :
    m_lightColor  ( 1.0f, 1.0f, 1.0f, 1.0f ),
    m_intensity   ( 1.0f                   ),
    m_description ( "Empty description "   ),
    m_status      ( LightStatus::FINE      )
{
    m_name = ++ Light::counter;
}

Light::Light( const QVector4D &lightColor
            , GLfloat          intensity
            , const QString   &description ) :
    m_lightColor  ( lightColor        ),
    m_intensity   ( intensity         ),
    m_description ( description       ),
    m_status      ( LightStatus::FINE )
{
    m_name = ++ Light::counter;
}

const Light & Light::operator = (const Light &light)
{
    m_lightColor  = light.m_lightColor;
    m_intensity   = light.m_intensity;
    m_description = light.m_description;

    return *this;
}

bool Light::operator ==(const Light &light) const
{
    bool equal = false;

    if(  m_lightColor == light.m_lightColor
      && m_intensity  == light.m_intensity )
    {
        equal = true;
    }

    return equal;
}

bool Light::operator !=(const Light &light) const
{
    return !(*this == light);
}

void Light::setLightColor(const QVector4D &lightColor)
{
    m_lightColor = lightColor;
}

void Light::setLightColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_lightColor.setX(r);
    m_lightColor.setY(g);
    m_lightColor.setZ(b);
    m_lightColor.setW(a);
}

void Light::setIntensity(GLfloat intensity)
{
    m_intensity = intensity;
}

void Light::setDescription(const QString &description)
{
    m_description = description;
}

Light::Light( const Light &light ) :
    m_lightColor  ( light.m_lightColor  ),
    m_intensity   ( light.m_intensity   ),
    m_name        ( light.m_name        ),
    m_description ( light.m_description ),
    m_status      ( light.m_status      )
{
}
