#ifndef SCENE_H
#define SCENE_H

#include "commonincludings.h"
#include "camera.h"
#include "renderer.h"

class Shape;
class Light;
class Program;

//! Implements OpenGL rendered scene.
class Scene
{
public:
    Scene();                                                                   //! Default constructor.
    Scene( const Renderer &renderer );                                         //! Parameterized constructor.
    Scene( const QList<std::weak_ptr<Shape> > &shapes );                       //! Parameterized constructor.
    Scene( const Camera   &camera   );                                         //! Parameterized constructor.
    Scene( const QString  &description );                                      //! Parameterized constructor.
    Scene( GLint           x                                                   //! Parameterized constructor.
         , GLint           y
         , GLsizei         width
         , GLsizei         height
         );
    Scene( const QHash<com_defs::RendererPrograms::Programs, std::weak_ptr<Program> > &programs );//! Parameterized constructor.
    Scene( const Renderer &renderer                                            //! Parameterized constructor.
         , const QList<std::weak_ptr<Shape> > &shapes
         );
    Scene( const QList<std::weak_ptr<Shape> > &shapes                          //! Parameterized constructor.
         , const Camera   &camera
         );
    Scene( const Renderer &renderer                                            //! Parameterized constructor.
         , const QList<std::weak_ptr<Shape> > &shapes
         , const Camera   &camera
         );
    Scene( const QHash<com_defs::RendererPrograms::Programs, std::weak_ptr<Program> > &programs   //! Parameterized constructor.
         , const QList<std::weak_ptr<Shape> > &shapes
         , const Camera   &camera
         );
    Scene( const QList<std::weak_ptr<Shape> > &shapes                          //! Parameterized constructor.
         , const Camera   &camera
         , GLint           x
         , GLint           y
         , GLsizei         width
         , GLsizei         height
         );
    Scene( const Renderer &renderer                                            //! Parameterized constructor.
         , const QList<std::weak_ptr<Shape> > &shapes
         , const Camera   &camera
         , GLint           x
         , GLint           y
         , GLsizei         width
         , GLsizei         height
         );
    Scene( const Renderer &renderer                                            //! Parameterized constructor.
         , const QList<std::weak_ptr<Shape> > &shapes
         , const Camera   &camera
         , GLint           x
         , GLint           y
         , GLsizei         width
         , GLsizei         height
         , const QString  &description
         );
    Scene( const QHash<com_defs::RendererPrograms::Programs, std::weak_ptr<Program> > &programs   //! Parameterized constructor.
         , const QList<std::weak_ptr<Shape> > &shapes
         , const Camera   &camera
         , GLint           x
         , GLint           y
         , GLsizei         width
         , GLsizei         height
         );
    Scene( const QHash<com_defs::RendererPrograms::Programs, std::weak_ptr<Program> > &programs   //! Parameterized constructor.
         , const QString  &rendererDescription
         , const QList<std::weak_ptr<Shape> > &shapes
         , const QList<std::weak_ptr<Light> > &lights
         , const Camera   &camera
         , GLint           x
         , GLint           y
         , GLsizei         width
         , GLsizei         height
         , const QString  &sceneDescription
         );

    virtual ~Scene();

    const Scene & operator = (const Scene &scene);                             //! Operator " =  ".
    bool  operator == (const Scene &scene) const;                              //! Operator " == ".
    bool  operator != (const Scene &scene) const;                              //! Operator " != ".

public:
    const Renderer & getRenderer() const { return m_renderer; }                //! Returns scene renderer object.
    Renderer & getRenderer() { return m_renderer; }                            //! Returns scene renderer object, overloaded function.
    void setRenderer(const Renderer &renderer);                                //! Sets scene renderer object.

    const QList<std::weak_ptr<Shape> > & getShapes() const { return m_shapes; }//! Returns QList of pointers to shape objects.
    QList<std::weak_ptr<Shape> > & getShapes() { return m_shapes; }            //! Returns QList of pointers to shape objects, overloaded function.
    void setShapes(const QList<std::weak_ptr<Shape> > &shapes);                //! Sets QList of pointers to shape objects.
    void addShape(std::weak_ptr<Shape> shape);                                 //! Adds shape pointer to QList of shape pointers.
    void removeShape(std::weak_ptr<Shape> shape);                              //! Removes shape pointer from QList of shape pointers.
    void removeAllShapes();                                                    //! Clears QList of shape pointers.

    const QList<std::weak_ptr<Light> > & getLights() const { return m_lights; }//! Returns QList of pointers to light objects.
    QList<std::weak_ptr<Light> > & getLights() { return m_lights; }            //! Returns QList of pointers to light objects, overloaded function.
    void setLights(const QList<std::weak_ptr<Light> > &lights);                //! Sets  QList of pointers to light objects.
    void addLight(std::weak_ptr<Light> light);                                 //! Adds light pointer to QList of light pointers.
    void removeLight(std::weak_ptr<Light> light);                              //! Removes light pointer from QList of light pointers.
    void removeAllLights();                                                    //! Clears QList of light pointers.

    const Camera & getCamera() const { return m_camera; }                      //! Returns scene camera.
    Camera & getCamera() { return m_camera; }                                  //! Returns scene camera, overloaded function.
    void setCamera(const Camera &camera);                                      //! Sets scene camera.

    GLuint getName() const { return m_name; }                                  //! Returns autogenerated name of scene.

    GLint getX() const { return m_x; }                                         //! Returns bottom-left x coordinate of viewport.
    GLint getY() const { return m_y; }                                         //! Returns bottom-left y coordinate of viewport.
    GLsizei getWidth() const { return m_width; }                               //! Returns width of viewport.
    GLsizei getHeight() const { return m_height; }                             //! Returns height of viewport.
    void setX(GLint x) { m_x = x; }                                            //! Sets bottom-left x coordinate of viewport.
    void setY(GLint y) { m_y = y; }                                            //! Sets bottom-left y coordinate of viewport.
    void setWidth(GLsizei width) { m_width = width; }                          //! Sets width of viewport.
    void setHeight(GLsizei height) { m_height = height; }                      //! Sets height of viewport.

    const QString & getDescription() const { return m_description; }           //! Returns scene description.
    void setDescription(const QString &description);                           //! Sets scene description.

public:
    static GLuint getCounter() { return counter; }                             //! Returns number of created scene objects.

    static std::shared_ptr<Scene> createObject();                              //! Creates new scene and returns pointer to it.

protected:
    Scene( const Scene &scene );                                               //! Copying constructor.

private:
    static GLuint counter;                        //! Counter of created scene objects.

private:
    Renderer                        m_renderer;   //! Scene renderer object.

    QList<std::weak_ptr<Shape> >    m_shapes;     //! QList of pointers to shape objects.
    QList<std::weak_ptr<Light> >    m_lights;     //! QList of pointers to light objects.

    Camera                          m_camera;     //! Scene camera.

    GLuint                          m_name;       //! Autogenerated name of scene.

    GLint                           m_x;          //! Bottom-left x coordinate of viewport, 0 by default.
    GLint                           m_y;          //! Bottom-left y coordinate of viewport, 0 by default.
    GLsizei                         m_width;      //! Width of viewport, 640 by default.
    GLsizei                         m_height;     //! Height of viewport, 480 by default.

    QString                         m_description;//! Description of scene.
};

#endif // SCENE_H
