#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "commonincludings.h"
#include "light.h"
#include "mesh.h"
#include "transforms.h"

class Renderer;
class Program;

//! Implements scene point light.
class PointLight : public Light
{
public:
    PointLight();                                        //! Default constructor.
    PointLight( const Mesh       &mesh                   //! Parameterized constructor.
              , const Transforms &transforms
              , GLfloat           radius
              , const QVector3D  &position
              );
    PointLight( const QVector4D        &lightColor       //! Parameterized constructor.
              , GLfloat                 intensity
              , const Mesh             &mesh
              , const Transforms       &transforms
              , GLfloat                 radius
              , const QVector3D        &position
              , std::weak_ptr<Program>  program       = std::weak_ptr<Program>()
              , const QString          &description   = "Empty description"
              );

    virtual ~PointLight();

    virtual com_defs::LightType getType() const override;                //! Returns light type.
    virtual void draw(Renderer *renderer) noexcept(false) override;      //! Draws into light buffer.

    const PointLight & operator = (const PointLight &light); //! Operator " =  ".
    bool  operator == (const PointLight &light) const;       //! Operator " == ".
    bool  operator != (const PointLight &light) const;       //! Operator " != ".

public:
    const Mesh & getMesh() const { return m_mesh; }      //! Returns light mesh.
    Mesh & getMesh() { return m_mesh; }                  //! Returns light mesh, overloaded function.
    void setMesh(const Mesh &mesh);                      //! Sets light mesh.

    const Transforms & getTransforms() const { return m_transforms; }   //! Returns light transforms.
    Transforms & getTransforms() { return m_transforms; }               //! Returns light transforms, overloaded function.
    void setTransforms(const Transforms &transforms);                   //! Sets light transforms.

    GLfloat getRadius() const { return m_radius; }       //! Returns light radius.
    void setRadius(GLfloat radius);                      //! Sets light radius.

    std::weak_ptr<Program> getProgram() { return m_program; }//! Returns pointer to point light shading program.
    void setProgram(std::weak_ptr<Program> program);         //! Sets pointer to point light shading program.

    const QVector3D & getPosition() const { return m_position; } //! Returns light position.
    QVector3D & getPosition() { return m_position; }             //! Returns light position, overloaded function.
    void setPosition(const QVector3D &position);                 //! Sets light position.
    void setPosition(GLfloat x, GLfloat y, GLfloat z);           //! Sets light position, overloaded function.

public:
    static GLuint getCounter() { return counter; }       //! Returns number of created point lights objects.

    static std::shared_ptr<PointLight> createObject();   //! Creates point light object and returns pointer to it.

protected:
    PointLight( const PointLight &light );               //! Copying constructor.

private:
    static GLuint counter;      //! Counter of created point light objects.

private:
    Mesh        m_mesh;         //! Light mesh.

    Transforms  m_transforms;   //! Light transforms.

    GLfloat     m_radius;       //! Light radius, 1.0f by default.

    std::weak_ptr<Program>  m_program;//! A pointer to point light shading program.    

    QVector3D   m_position;     //! Light position in 3D space, { 0.0f, 0.0f, 0.0f } by default.
};

#endif // POINTLIGHT_H
