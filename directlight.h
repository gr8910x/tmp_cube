#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "commonincludings.h"
#include "light.h"
#include "camera.h"

class Renderer;
class Program;

//! Implements scene direct light.
class DirectLight : public Light
{
public:
    DirectLight();                                                  //! Default constructor.
    DirectLight( const QVector3D        &direction );               //! Parameterized constructor.
    DirectLight( const QVector4D        &lightColor                 //! Parameterized constructor.
               , GLfloat                 intensity
               , const QVector3D        &direction
               , std::weak_ptr<Program>  program      = std::weak_ptr<Program>()
               , const QString          &description  = "Empty description" );

    virtual ~DirectLight() {}

    virtual com_defs::LightType getType() const override;           //! Returns light type.
    virtual void draw(Renderer *renderer) noexcept(false) override; //! Draws into light buffer.

    const DirectLight & operator = (const DirectLight &light);      //! Operator " =  ".
    bool  operator == (const DirectLight &light) const;             //! Operator " == ".
    bool  operator != (const DirectLight &light) const;             //! Operator " != ".

public:
    const QVector3D & getDirection() const { return m_direction; }  //! Returns direction of light.
    QVector3D & getDirection() { return m_direction; }              //! Returns direction of light, overloaded function.
    void setDirection(const QVector3D &direction);                  //! Sets direction of light.
    void setDirection(GLfloat x, GLfloat y, GLfloat z);             //! Sets direction of light, overloaded function.

    std::weak_ptr<Program> getProgram() { return m_program; }       //! Returns pointer to direct light shading program.
    void setProgram(std::weak_ptr<Program> program);                //! Sets pointer to direct light shading program.

    const Camera & getShadowCamera() const { return m_shadowCamera; }//! Returns shadow camera object.
    Camera & getShadowCamera() { return m_shadowCamera; }            //! Returns shadow camera object, overloaded function.
    void setShadowCamera(const Camera &shadowCamera);                //! Sets shadow camera object.

public:
    static GLuint getCounter() { return counter; }     //! Returns number of created direction lights objects.

    static std::shared_ptr<DirectLight> createObject();//! Creates direction light object and returns pointer to it.

protected:
    DirectLight( const DirectLight &light );           //! Copying constructor.    

private:
    void drawLight(Renderer *renderer) noexcept(false); //! Draws light.
    void drawShadow(Renderer *renderer) noexcept(false);//! Draws shadow.

private:
    static GLuint counter;      //! Counter of created direction light objects.

private:
    QVector3D   m_direction;    //! Direction of light, { 0.0f,  0.0f, -1.0f } by default.

    std::weak_ptr<Program> m_program; //! A pointer to direct light shading program.

    Camera      m_shadowCamera; //! Shadow camera object.
};

#endif // DIRECTLIGHT_H
