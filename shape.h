#ifndef SHAPE_H
#define SHAPE_H

#include "commonincludings.h"
#include "ishape.h"
#include "mesh.h"
#include "transforms.h"

class Program;
class Camera;
class Texture;

//! Implements a shape in 3D-space.
class Shape : public IShape
{
public:
    Shape();                                                         //! Default constructor.
    Shape( const Mesh &mesh );                                       //! Parameterized constructor.
    Shape( const Transforms &transforms );                           //! Parameterized constructor.
    Shape( std::weak_ptr<Program> program );                         //! Parameterized constructor.
    Shape( const QString &description );                             //! Parameterized constructor.
    Shape( const Mesh       &mesh                                    //! Parameterized constructor.
         , const Transforms &transforms
         );
    Shape( const Mesh             &mesh                              //! Parameterized constructor.
         , const Transforms       &transforms
         , std::weak_ptr<Program>  program
         );
    Shape( const Mesh             &mesh                              //! Parameterized constructor.
         , const Transforms       &transforms
         , std::weak_ptr<Program>  program
         , const QString          &description
         );
    Shape( const Mesh             &mesh                              //! Parameterized constructor.
         , const Transforms       &transforms
         , std::weak_ptr<Program>  program
         , const QHash<QString, std::weak_ptr<Texture> > &textures
         , const QString          &description
         );
    Shape( const QVector<Vertex>  &vertices                          //! Parameterized constructor.
         , const QVector<Index>   &indices
         , GLenum                  mode
         , const QString          &meshDescription
         , const Transforms       &transforms
         , std::weak_ptr<Program>  program
         , const QHash<QString, std::weak_ptr<Texture> > &textures
         , const QString          &shapeDescription
         );
    Shape( const QVector<Vertex>  &vertices                          //! Parameterized constructor.
         , const QVector<Index>   &indices
         , GLenum                  mode
         , const QString          &meshDescription
         , GLfloat                 translationX
         , GLfloat                 translationY
         , GLfloat                 translationZ
         , GLfloat                 rotationAngle
         , GLfloat                 rotationX
         , GLfloat                 rotationY
         , GLfloat                 rotationZ
         , GLfloat                 scalingX
         , GLfloat                 scalingY
         , GLfloat                 scalingZ
         , std::weak_ptr<Program>  program
         , const QString          &shapeDescription
         );
    Shape( const QVector<Vertex>  &vertices                          //! Parameterized constructor.
         , const QVector<Index>   &indices
         , GLenum                  mode
         , const QString          &meshDescription
         , GLfloat                 translationX
         , GLfloat                 translationY
         , GLfloat                 translationZ
         , GLfloat                 rotationAngle
         , GLfloat                 rotationX
         , GLfloat                 rotationY
         , GLfloat                 rotationZ
         , GLfloat                 scalingX
         , GLfloat                 scalingY
         , GLfloat                 scalingZ
         , std::weak_ptr<Program>  program
         , const QHash<QString, std::weak_ptr<Texture> > &textures
         , const QString          &shapeDescription
         );

    virtual ~Shape();

    virtual void draw(const Camera *camera) noexcept(false) override;      //! Draws this shape.
    virtual void drawShadow(const Camera *camera) noexcept(false) override;//! Draws shape shadow to texture.

    const Shape & operator = (const Shape &shape);                         //! Operator " =  ".
    bool  operator == (const Shape &shape) const;                          //! Operator " == ".
    bool  operator != (const Shape &shape) const;                          //! Operator " != ".

public:
    const Mesh & getMesh() const { return m_mesh; }                        //! Returns shape mesh object.
    Mesh & getMesh() { return m_mesh; }                                    //! Returns shape mesh object, overloaded function.
    void setMesh(const Mesh &mesh);                                        //! Sets shape mesh object.

    const Transforms & getTransforms() const { return m_transforms; }      //! Returns applied transforms.
    void  setTransforms(const Transforms &transforms);                     //! Sets applied transforms.

    std::weak_ptr<Program> getProgram() { return m_program; }              //! Returns pointer to shape shading program.
    void setProgram(std::weak_ptr<Program> program);                       //! Sets pointer to shape shading program.

    std::weak_ptr<Program> getShadowProgram() { return m_shadowProgram; }  //! Returns pointer to shape depth program.
    void setShadowProgram(std::weak_ptr<Program> shadowProgram);           //! Sets pointer to shape depth program.

    const QHash<QString, std::weak_ptr<Texture> > & getTextures() const { return m_textures; }//! Returns shape textures.
    QHash<QString, std::weak_ptr<Texture> > & getTextures() { return m_textures; }            //! Returns shape textures, overloaded function.
    void setTextures(const QHash<QString, std::weak_ptr<Texture> > &textures);                //! Sets shape textures.

    GLuint getName() const { return m_name; }                              //! Returns autogenerated shape name.

    const QString &getDescription() const { return m_description; }        //! Returns description of shape.
    void setDescription(const QString &description);                       //! Sets description of shape.

    uint getStatus() const { return m_status; }                            //! Returns shape object status bitmask.

public:
    static GLuint getCounter() { return counter; }                         //! Returns number of created shapes.

    static std::shared_ptr<Shape> createObject();                          //! Creates new shape and returns pointer to it.

protected:
    Shape( const Shape &shape );                                           //! Copying constructor.

    void setStatus(uint status) { m_status = status; }                     //! Sets shape object status bitmask.

private:
    static GLuint counter;                     //! Counter of created shapes objects.

private:
    Mesh                       m_mesh;         //! Shape mesh object.

    Transforms                 m_transforms;   //! Transforms applied to this shape.

    std::weak_ptr<Program>     m_program;      //! A pointer to shape shading program.
    std::weak_ptr<Program>     m_shadowProgram;//! A pointer to shape shadow shading program.
    QHash<QString, std::weak_ptr<Texture> >   m_textures; //! Shape textures.

    GLuint                     m_name;         //! Autogenerated shape name.

    QString                    m_description;  //! Description of shape.

    uint                       m_status;       //! Shape object status bitmask.
};

#endif // SHAPE_H
