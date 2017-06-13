#ifndef LIGHT_H
#define LIGHT_H

#include "commonincludings.h"
#include "ilight.h"

class Renderer;

//! Implements scene light.
class Light : public ILight
{
public:
    Light();                                                            //! Default constructor.
    Light( const QVector4D &lightColor                                  //! Parameterized constructor.
         , GLfloat          intensity
         , const QString   &description   = "Empty description" );

    virtual ~Light() {}

    virtual com_defs::LightType getType() const override = 0;           //! Returns light type.
    virtual void draw(Renderer *renderer) noexcept(false) override = 0; //! Draws into light buffer.

    const Light & operator = (const Light &light);                      //! Operator " =  ".
    bool  operator == (const Light &light) const;                       //! Operator " == ".
    bool  operator != (const Light &light) const;                       //! Operator " != ".

public:
    const QVector4D & getLightColor() const { return m_lightColor; }    //! Returns color of light.
    QVector4D & getLightColor() { return m_lightColor; }                //! Returns color of light, overloaded function.
    void setLightColor(const QVector4D &lightColor);                    //! Sets color of light.
    void setLightColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);     //! Sets color of light, overloaded function.

    GLfloat getIntensity() { return m_intensity; }                      //! Returns intensity of light.
    void setIntensity(GLfloat intensity);                               //! Sets intensity of light.

    GLuint getName() const { return m_name; }                           //! Returns autogenerated name of light.

    const QString & getDescription() const { return m_description; }    //! Returns description of light.
    void setDescription(const QString &description);                    //! Sets description of light.

    uint & getStatus() { return m_status; }                             //! Returns light status bitmaks.

public:
    static GLuint getCounter() { return counter; }                      //! Returns number of created light objects.

protected:
     Light( const Light &light );                                       //! Copying constructor.

     void setStatus(uint status) { m_status = status; }                 //! Sets light status bitmaks.

private:
    static GLuint counter;      //! Counter of created light objects.

private:
    QVector4D   m_lightColor;   //! Color of light, { 1.0f, 1.0f, 1.0f, 1.0f } by default.
    GLfloat     m_intensity;    //! Intensity of light, 1.0f by default.

    GLuint      m_name;         //! Autogenerated name of light.

    QString     m_description;  //! Light description.

    uint        m_status;       //! Light status bitmaks;
};

#endif // LIGHT_H
