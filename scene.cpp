#include "scene.h"
#include "shape.h"
#include "light.h"
#include "program.h"

GLuint Scene::counter = 0;

Scene::Scene() :
    m_renderer    ( this                ),
    m_shapes      (                     ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const Renderer &renderer ) :
    m_renderer    ( renderer            ),
    m_shapes      (                     ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const QList<std::weak_ptr<Shape> > &shapes ) :
    m_renderer    ( this                ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const Camera &camera ) :
    m_renderer    ( this                ),
    m_shapes      (                     ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene(const QString &description) :
    m_renderer    ( this                ),
    m_shapes      (                     ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( description         )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( GLint   x
            , GLint   y
            , GLsizei width
            , GLsizei height ) :
    m_renderer    ( this                ),
    m_shapes      (                     ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( x                   ),
    m_y           ( y                   ),
    m_width       ( width               ),
    m_height      ( height              ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const QHash<common_definitions::RendererPrograms::Programs, std::weak_ptr<Program> > &programs ) :
    m_renderer    ( this, programs      ),
    m_shapes      (                     ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const Renderer &renderer
            , const QList<std::weak_ptr<Shape> > &shapes
            ) :
    m_renderer    ( renderer            ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      (                     ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const QList<std::weak_ptr<Shape> > &shapes
            , const Camera   &camera
            ) :
    m_renderer    ( this                ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const Renderer &renderer
            , const QList<std::weak_ptr<Shape> > &shapes
            , const Camera   &camera
            ) :
    m_renderer    ( renderer            ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const QHash<common_definitions::RendererPrograms::Programs, std::weak_ptr<Program> > &programs
            , const QList<std::weak_ptr<Shape> > &shapes
            , const Camera   &camera
            ) :
    m_renderer    ( this, programs      ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( 0                   ),
    m_y           ( 0                   ),
    m_width       ( 640                 ),
    m_height      ( 480                 ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const QList<std::weak_ptr<Shape> > &shapes
            , const Camera   &camera
            , GLint           x
            , GLint           y
            , GLsizei         width
            , GLsizei         height
            ) :
    m_renderer    ( this                ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( x                   ),
    m_y           ( y                   ),
    m_width       ( width               ),
    m_height      ( height              ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const Renderer &renderer
            , const QList<std::weak_ptr<Shape> > &shapes
            , const Camera   &camera
            , GLint           x
            , GLint           y
            , GLsizei         width
            , GLsizei         height
            ) :
    m_renderer    ( renderer            ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( x                   ),
    m_y           ( y                   ),
    m_width       ( width               ),
    m_height      ( height              ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene( const Renderer                     &renderer
            , const QList<std::weak_ptr<Shape> > &shapes
            , const Camera                       &camera
            , GLint                               x
            , GLint                               y
            , GLsizei                             width
            , GLsizei                             height
            , const QString                      &description
            ) :
    m_renderer    ( renderer            ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( x                   ),
    m_y           ( y                   ),
    m_width       ( width               ),
    m_height      ( height              ),
    m_description ( description         )
{
    m_name = ++Scene::counter;
}

Scene::Scene( const QHash<common_definitions::RendererPrograms::Programs, std::weak_ptr<Program> > &programs
            , const QList<std::weak_ptr<Shape> > &shapes
            , const Camera   &camera
            , GLint           x
            , GLint           y
            , GLsizei         width
            , GLsizei         height
            ) :
    m_renderer    ( this, programs      ),
    m_shapes      ( shapes              ),
    m_lights      (                     ),
    m_camera      ( camera              ),
    m_x           ( x                   ),
    m_y           ( y                   ),
    m_width       ( width               ),
    m_height      ( height              ),
    m_description ( "Empty description" )
{
    m_name = ++ Scene::counter;
}

Scene::Scene(const QHash<common_definitions::RendererPrograms::Programs, std::weak_ptr<Program> > &programs
            , const QString  &rendererDescription
            , const QList<std::weak_ptr<Shape> > &shapes
            , const QList<std::weak_ptr<Light> > &lights
            , const Camera   &camera
            , GLint           x
            , GLint           y
            , GLsizei         width
            , GLsizei         height
            , const QString  &sceneDescription
            ) :
    m_renderer    ( this, programs, rendererDescription ),
    m_shapes      ( shapes                              ),
    m_lights      ( lights                              ),
    m_camera      ( camera                              ),
    m_x           ( x                                   ),
    m_y           ( y                                   ),
    m_width       ( width                               ),
    m_height      ( height                              ),
    m_description ( sceneDescription                    )
{
    m_name = ++ Scene::counter;
}

Scene::~Scene()
{
    m_renderer.deleteBuffers();    
}

const Scene & Scene::operator = (const Scene &scene)
{
    m_renderer    = scene.m_renderer;
    m_shapes      = scene.m_shapes;
    m_lights      = scene.m_lights;
    m_camera      = scene.m_camera;
    m_x           = scene.m_x;
    m_y           = scene.m_y;
    m_width       = scene.m_width;
    m_height      = scene.m_height;
    m_description = scene.m_description;

    return *this;
}

bool Scene::operator == (const Scene &scene) const
{
    bool equal = false;

    bool shapesEqual = false;
    if( m_shapes.length() == scene.m_shapes.length() )
    {
        shapesEqual = true;
        for( int i = 0; i < m_shapes.length(); ++i )
        {
            std::shared_ptr<const Shape> thisShape    = m_shapes[i].lock();
            std::shared_ptr<const Shape> anotherShape = scene.m_shapes[i].lock();

            if( thisShape.get() != anotherShape.get() )
            {
                shapesEqual = false;
                break;
            }
        }
    }

    bool lightsEqual = false;
    if( m_lights.length() == scene.m_lights.length() )
    {
        lightsEqual = true;
        for( int i = 0; i < m_lights.length(); ++i )
        {
            std::shared_ptr<const Light> thisLight = m_lights[i].lock();
            std::shared_ptr<const Light> anotherLight = scene.m_lights[i].lock();

            if( thisLight.get() != anotherLight.get() )
            {
                lightsEqual = false;
                break;
            }
        }
    }

    if(  m_renderer == scene.m_renderer
      && shapesEqual
      && lightsEqual
      && m_camera   == scene.m_camera
      && m_x        == scene.m_x
      && m_y        == scene.m_y
      && m_width    == scene.m_width
      && m_height   == scene.m_height
      )
    {
        equal = true;
    }

    return equal;
}

bool Scene::operator != (const Scene &scene) const
{
    return !(*this == scene);
}

void Scene::setRenderer(const Renderer &renderer)
{
    m_renderer = renderer;
}

void Scene::setShapes(const QList<std::weak_ptr<Shape> > &shapes)
{
    m_shapes = shapes;
}

void Scene::addShape(std::weak_ptr<Shape> shape)
{
    m_shapes << shape;
}

void Scene::removeShape(std::weak_ptr<Shape> shape)
{
    std::shared_ptr<Shape> shapeToRemove = shape.lock();

    uint i = 0;
    for( std::weak_ptr<Shape> weakShape : m_shapes )
    {
        std::shared_ptr<Shape> tmpShape = weakShape.lock();

        if( shapeToRemove.get() == tmpShape.get() )
        {
            m_shapes.removeAt(i);
            break;
        }

        ++ i;
    }
}

void Scene::removeAllShapes()
{
    m_shapes.clear();
}

void Scene::setLights(const QList<std::weak_ptr<Light> > &lights)
{
    m_lights = lights;
}

void Scene::addLight(std::weak_ptr<Light> light)
{
    m_lights << light;
}

void Scene::removeLight(std::weak_ptr<Light> light)
{
    std::shared_ptr<Light> lightToRemove = light.lock();

    uint i = 0;
    for( std::weak_ptr<Light> weakLight : m_lights )
    {
        std::shared_ptr<Light> tmpLight = weakLight.lock();

        if( lightToRemove.get() == tmpLight.get() )
        {
            m_lights.removeAt(i);
            break;
        }

        ++ i;
    }
}

void Scene::removeAllLights()
{
    m_lights.clear();
}

void Scene::setCamera(const Camera &camera)
{
    m_camera = camera;
}

void Scene::setDescription(const QString &description)
{
    m_description = description;
}

std::shared_ptr<Scene> Scene::createObject()
{
    return std::make_shared<Scene>();
}

Scene::Scene( const Scene &scene ) :
    m_renderer    ( scene.m_renderer    ),
    m_shapes      ( scene.m_shapes      ),
    m_lights      ( scene.m_lights      ),
    m_camera      ( scene.m_camera      ),
    m_name        ( scene.m_name        ),
    m_x           ( scene.m_x           ),
    m_y           ( scene.m_y           ),
    m_width       ( scene.m_width       ),
    m_height      ( scene.m_height      ),
    m_description ( scene.m_description )
{
}
