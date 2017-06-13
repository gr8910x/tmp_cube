#include "enginecontext.h"
#include "enginecontextexception.h"
#include "engine.h"
#include "shape.h"
#include "light.h"
#include "pointlight.h"
#include "directlight.h"
#include "mesh.h"
#include "scene.h"
#include "program.h"
#include "texture.h"
#include "appwindow.h"
#include "eventshandler.h"
#include "openglcontext.h"

using namespace com_defs;

uint EngineContext::counter = 0;

EngineContext::EngineContext() :
    m_engine                  ( nullptr                        ),
    m_shapes                  (                                ),
    m_scenes                  (                                ),
    m_programs                (                                ),
    m_eventsHandlers          (                                ),
    m_windows                 (                                ),
    m_openGLContexts          (                                ),
    m_shapesFactories         (                                ),
    m_scenesFactories         (                                ),
    m_openGLContextsFactories (                                ),
    m_windowsFactories        (                                ),
    m_programsFactories       (                                ),
    m_eventsHandlersFactories (                                ),
    m_selectedScene           (                                ),
    m_selectedWindow          (                                ),
    m_selectedOpenGLContext   (                                ),
    m_description             ( "Empty description"            ),
    m_status                  ( EngineContextStatus::NO_ENGINE )
{
    m_name = ++ EngineContext::counter;
}

EngineContext::EngineContext( Engine        *engine
                            , const QString &description ) :
    m_engine                  ( engine                         ),
    m_shapes                  (                                ),
    m_scenes                  (                                ),
    m_programs                (                                ),
    m_eventsHandlers          (                                ),
    m_windows                 (                                ),
    m_openGLContexts          (                                ),
    m_shapesFactories         (                                ),
    m_scenesFactories         (                                ),
    m_openGLContextsFactories (                                ),
    m_windowsFactories        (                                ),
    m_programsFactories       (                                ),
    m_eventsHandlersFactories (                                ),
    m_selectedScene           (                                ),
    m_selectedWindow          (                                ),
    m_selectedOpenGLContext   (                                ),
    m_description             ( description                    ),
    m_status                  ( EngineContextStatus::FINE      )
{
    m_name = ++ EngineContext::counter;
}

EngineContext::EngineContext( const EngineContext &context ) :
    m_engine                  ( context.m_engine                  ),
    m_shapes                  ( context.m_shapes                  ),
    m_scenes                  ( context.m_scenes                  ),
    m_programs                ( context.m_programs                ),
    m_eventsHandlers          ( context.m_eventsHandlers          ),
    m_windows                 ( context.m_windows                 ),
    m_openGLContexts          ( context.m_openGLContexts          ),
    m_shapesFactories         ( context.m_shapesFactories         ),
    m_scenesFactories         ( context.m_scenesFactories         ),
    m_openGLContextsFactories ( context.m_openGLContextsFactories ),
    m_windowsFactories        ( context.m_windowsFactories        ),
    m_programsFactories       ( context.m_programsFactories       ),
    m_eventsHandlersFactories ( context.m_eventsHandlersFactories ),
    m_selectedScene           ( context.m_selectedScene           ),
    m_selectedWindow          ( context.m_selectedWindow          ),
    m_selectedOpenGLContext   ( context.m_selectedOpenGLContext   ),
    m_description             ( context.m_description             ),
    m_name                    ( context.m_name                    ),
    m_status                  ( context.m_status                  )
{
}

const EngineContext & EngineContext::operator = (const EngineContext &context)
{
    m_engine                  = context.m_engine;
    m_shapes                  = context.m_shapes;
    m_scenes                  = context.m_scenes;
    m_programs                = context.m_programs;
    m_eventsHandlers          = context.m_eventsHandlers;
    m_windows                 = context.m_windows;
    m_openGLContexts          = context.m_openGLContexts;
    m_shapesFactories         = context.m_shapesFactories;
    m_scenesFactories         = context.m_scenesFactories;
    m_openGLContextsFactories = context.m_openGLContextsFactories;
    m_windowsFactories        = context.m_windowsFactories;
    m_programsFactories       = context.m_programsFactories;
    m_eventsHandlersFactories = context.m_eventsHandlersFactories;
    m_selectedScene           = context.m_selectedScene;
    m_selectedWindow          = context.m_selectedWindow;
    m_selectedOpenGLContext   = context.m_selectedOpenGLContext;
    m_description             = context.m_description;

    ( !m_engine ) ? m_status |=  EngineContextStatus::NO_ENGINE
                  : m_status &= ~EngineContextStatus::NO_ENGINE;

    return *this;
}

std::weak_ptr<Shape> EngineContext::createShape( const QString                                  &factoryName
                                               , const QString                                  &key
                                               , const Mesh                                     &mesh
                                               , const Transforms                               &transforms
                                               , std::weak_ptr<Program>                          program
                                               , std::weak_ptr<Program>                          shadowProgram
                                               , const QHash<QString, std::weak_ptr<Texture> >  &textures
                                               , const QString                                  &description
                                               ) noexcept(false)
{
    ( !m_shapesFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_SHAPES_FACTORY
                                                 : m_status &= ~EngineContextStatus::INVALID_SHAPES_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_SHAPES_FACTORY) == EngineContextStatus::INVALID_SHAPES_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<Shape> shape = m_shapesFactories.value(factoryName)();
    shape->setMesh(mesh);
    shape->setTransforms(transforms);
    shape->setProgram(program);
    shape->setTextures(textures);
    shape->setDescription(description);
    shape->setShadowProgram(shadowProgram);

    m_shapes.insert(key, shape);

    return std::weak_ptr<Shape>(shape);
}

std::weak_ptr<Shape> EngineContext::createShape( const QString                                 &factoryName
                                               , const QString                                 &key
                                               , const QVector<Vertex>                         &vertices
                                               , const QVector<Index>                          &indices
                                               , GLenum                                         mode
                                               , GLfloat                                        translationX
                                               , GLfloat                                        translationY
                                               , GLfloat                                        translationZ
                                               , GLfloat                                        rotationAngle
                                               , GLfloat                                        rotationX
                                               , GLfloat                                        rotationY
                                               , GLfloat                                        rotationZ
                                               , GLfloat                                        scalingX
                                               , GLfloat                                        scalingY
                                               , GLfloat                                        scalingZ
                                               , std::weak_ptr<Program>                         program
                                               , std::weak_ptr<Program>                         shadowProgram
                                               , const QHash<QString, std::weak_ptr<Texture> > &textures
                                               , const QString                                 &meshDescription
                                               , const QString                                 &shapeDescription
                                               ) noexcept(false)
{
    ( !m_shapesFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_SHAPES_FACTORY
                                                 : m_status &= ~EngineContextStatus::INVALID_SHAPES_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_SHAPES_FACTORY) == EngineContextStatus::INVALID_SHAPES_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<Shape> shape = m_shapesFactories.value(factoryName)();
    Mesh mesh(vertices, indices, mode, meshDescription);
    shape->setMesh(mesh);
    Transforms transforms(translationX, translationY, translationZ, rotationAngle, rotationX, rotationY, rotationZ, scalingX, scalingY, scalingZ);
    shape->setTransforms(transforms);
    shape->setProgram(program);
    shape->setTextures(textures);
    shape->setDescription(shapeDescription);
    shape->setShadowProgram(shadowProgram);

    m_shapes.insert(key, shape);

    return std::weak_ptr<Shape>(shape);
}

std::weak_ptr<PointLight> EngineContext::createPointLight(const QString          &factoryName
                                                         , const QString          &key
                                                         , const QVector4D        &lightColor
                                                         , GLfloat                 radius
                                                         , GLfloat                 intensity
                                                         , const Mesh             &mesh
                                                         , const Transforms       &transforms
                                                         , const QVector3D        &position
                                                         , std::weak_ptr<Program>  program
                                                         , const QString          &description
                                                         ) noexcept(false)
{
    ( !m_pointLightsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_POINT_LIGHTS_FACTORY
                                                      : m_status &= ~EngineContextStatus::INVALID_POINT_LIGHTS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_POINT_LIGHTS_FACTORY) == EngineContextStatus::INVALID_POINT_LIGHTS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<PointLight> pointLight = m_pointLightsFactories.value(factoryName)();
    pointLight->setLightColor(lightColor);
    pointLight->setIntensity(intensity);
    pointLight->setMesh(mesh);
    pointLight->setTransforms(transforms);    
    pointLight->setPosition(position);
    pointLight->setProgram(program);
    pointLight->setRadius(radius);
    pointLight->setDescription(description);

    m_lights.insert(key, pointLight);

    return std::weak_ptr<PointLight>(pointLight);
}

std::weak_ptr<DirectLight> EngineContext::createDirectLight( const QString          &factoryName
                                                           , const QString          &key
                                                           , const QVector4D        &lightColor
                                                           , const QVector3D        &lightDirection
                                                           , const Camera           &shadowCamera
                                                           , GLfloat                 intensity
                                                           , std::weak_ptr<Program>  program
                                                           , const QString          &description
                                                           ) noexcept(false)
{
    ( !m_directLightsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_DIRECT_LIGHTS_FACTORY
                                                       : m_status &= ~EngineContextStatus::INVALID_DIRECT_LIGHTS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_DIRECT_LIGHTS_FACTORY) == EngineContextStatus::INVALID_DIRECT_LIGHTS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<DirectLight> directLight = m_directLightsFactories.value(factoryName)();
    directLight->setLightColor(lightColor);
    directLight->setIntensity(intensity);
    directLight->setDirection(lightDirection);
    directLight->setProgram(program);
    directLight->setDescription(description);
    directLight->setShadowCamera(shadowCamera);

    m_lights.insert(key, directLight);

    return std::weak_ptr<DirectLight>(directLight);
}

std::weak_ptr<Scene> EngineContext::createScene(const QString                      &factoryName
                                               , const QString                      &key
                                               , const Renderer                     &renderer
                                               , const Camera                       &camera
                                               , GLint                               x
                                               , GLint                               y
                                               , GLsizei                             width
                                               , GLsizei                             height
                                               , const QList<std::weak_ptr<Shape> > &shapes
                                               , const QList<std::weak_ptr<Light> > &lights
                                               , const QString                      &description ) noexcept(false)
{
    ( !m_scenesFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_SCENES_FACTORY
                                                 : m_status &= ~EngineContextStatus::INVALID_SCENES_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_SCENES_FACTORY) == EngineContextStatus::INVALID_SCENES_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<Scene> scene = m_scenesFactories.value(factoryName)();
    scene->setRenderer(renderer);
    scene->setCamera(camera);
    scene->setX(x);
    scene->setY(y);
    scene->setWidth(width);
    scene->setHeight(height);
    scene->setShapes(shapes);
    scene->setLights(lights);
    scene->setDescription(description);

    m_scenes.insert(key, scene);

    return std::weak_ptr<Scene>(scene);
}

std::weak_ptr<Scene> EngineContext::createScene(const QString                      &factoryName
                                               , const QString                      &key
                                               , const Camera                       &camera
                                               , const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &programs
                                               , GLint                               x
                                               , GLint                               y
                                               , GLsizei                             width
                                               , GLsizei                             height
                                               , const QList<std::weak_ptr<Shape> > &shapes
                                               , const QList<std::weak_ptr<Light> > &lights
                                               , const QString                      &rendererDescription
                                               , const QString                      &sceneDescription
                                               ) noexcept(false)
{
    ( !m_scenesFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_SCENES_FACTORY
                                                 : m_status &= ~EngineContextStatus::INVALID_SCENES_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_SCENES_FACTORY) == EngineContextStatus::INVALID_SCENES_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<Scene> scene = m_scenesFactories.value(factoryName)();
    scene->getRenderer().setPrograms(programs);
    scene->setCamera(camera);
    scene->setX(x);
    scene->setY(y);
    scene->setWidth(width);
    scene->setHeight(height);
    scene->setShapes(shapes);
    scene->setLights(lights);
    scene->getRenderer().setDescription(rendererDescription);
    scene->setDescription(sceneDescription);

    m_scenes.insert(key, scene);

    return std::weak_ptr<Scene>(scene);
}

std::weak_ptr<Program> EngineContext::createProgram( const QString        &factoryName
                                                   , const QString        &key
                                                   , const VertexShader   &vertexShader
                                                   , const FragmentShader &fragmentShader
                                                   , const QString        &description
                                                   ) noexcept(false)
{
    ( !m_programsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_PROGRAMS_FACTORY
                                                   : m_status &= ~EngineContextStatus::INVALID_PROGRAMS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_PROGRAMS_FACTORY) == EngineContextStatus::INVALID_PROGRAMS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<Program> program = m_programsFactories.value(factoryName)();
    program->setVertexShader(vertexShader);
    program->setFragmentShader(fragmentShader);
    program->setDescription(description);

    m_programs.insert(key, program);

    return std::weak_ptr<Program>(program);
}

std::weak_ptr<Program> EngineContext::createProgram( const QString &factoryName
                                                   , const QString &key
                                                   , const QString &vertexPath
                                                   , const QString &fragmentPath
                                                   , const QString &vertexDescription
                                                   , const QString &fragmentDescription
                                                   , const QString &programDescription
                                                   ) noexcept(false)
{
    ( !m_programsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_PROGRAMS_FACTORY
                                                   : m_status &= ~EngineContextStatus::INVALID_PROGRAMS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_PROGRAMS_FACTORY) == EngineContextStatus::INVALID_PROGRAMS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<Program> program = m_programsFactories.value(factoryName)();
    program->getVertexShader().setPath(vertexPath);
    program->getVertexShader().setDescription(vertexDescription);
    program->getFragmentShader().setPath(fragmentPath);
    program->getFragmentShader().setDescription(fragmentDescription);
    program->setDescription(programDescription);

    m_programs.insert(key, program);

    return std::weak_ptr<Program>(program);
}

std::weak_ptr<EventsHandler> EngineContext::createEventsHandler( const QString &factoryName
                                                               , const QString &key
                                                               , const QString &description )
{
    ( !m_eventsHandlersFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_EVENTS_HANDLERS_FACTORY
                                                         : m_status &= ~EngineContextStatus::INVALID_EVENTS_HANDLERS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_EVENTS_HANDLERS_FACTORY) == EngineContextStatus::INVALID_EVENTS_HANDLERS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<EventsHandler> eventsHandler = m_eventsHandlersFactories.value(factoryName)();
    eventsHandler->setDescription(description);

    m_eventsHandlers.insert(key, eventsHandler);

    return std::weak_ptr<EventsHandler>(eventsHandler);
}

std::weak_ptr<AppWindow> EngineContext::createWindow( const QString &factoryName
                                                    , const QString &key
                                                    , const QString &title
                                                    , std::weak_ptr<EventsHandler> eventsHandler
                                                    , int            x
                                                    , int            y
                                                    , int            width
                                                    , int            height
                                                    , const QString &description
                                                    , Uint32         sdlWindowInitFlags
                                                    , Uint32         sdlRendererInitFlags
                                                    ) noexcept(false)
{
    ( !m_windowsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_WINDOWS_FACTORY
                                                  : m_status &= ~EngineContextStatus::INVALID_WINDOWS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_WINDOWS_FACTORY) == EngineContextStatus::INVALID_WINDOWS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<AppWindow> window = m_windowsFactories.value(factoryName)();
    window->setTitle(title);
    window->setEventsHandler(eventsHandler);
    window->setX(x);
    window->setY(y);
    window->setWidth(width);
    window->setHeight(height);
    window->setDescription(description);
    window->setSDLWindowInitFlags(sdlWindowInitFlags);
    window->setSDLRendererInitFlags(sdlRendererInitFlags);
    window->setEngine(m_engine);
    window->setKey(key);

    m_windows.insert(key, window);

    return std::weak_ptr<AppWindow>(window);
}

std::weak_ptr<OpenGLContext> EngineContext::createOpenGLContext( const QString            &factoryName
                                                               , const QString            &key
                                                               , std::weak_ptr<AppWindow>  window
                                                               , const QVector4D          &clearColor
                                                               , GLfloat                   clearDepth
                                                               , const QString            &description
                                                               ) noexcept(false)
{
    ( !m_openGLContextsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY
                                                         : m_status &= ~EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY) == EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<OpenGLContext> openGLContext = m_openGLContextsFactories.value(factoryName)();
    openGLContext->setClearColor(clearColor);
    openGLContext->setClearDepth(clearDepth);
    openGLContext->setDescription(description);
    openGLContext->setWindow(window);
    openGLContext->setEngine(m_engine);

    m_openGLContexts.insert(key, openGLContext);

    return std::weak_ptr<OpenGLContext>(openGLContext);
}

std::weak_ptr<OpenGLContext> EngineContext::createOpenGLContext( const QString            &factoryName
                                                               , const QString            &key
                                                               , std::weak_ptr<AppWindow>  window
                                                               , GLfloat                   clearRed
                                                               , GLfloat                   clearGreen
                                                               , GLfloat                   clearBlue
                                                               , GLfloat                   clearAlpha
                                                               , GLfloat                   clearDepth
                                                               , const QString            &description
                                                               ) noexcept(false)
{
    ( !m_openGLContextsFactories.contains(factoryName) ) ? m_status |=  EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY
                                                         : m_status &= ~EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY;
    if( (m_status & EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY) == EngineContextStatus::INVALID_OPENGL_CONTEXTS_FACTORY )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    std::shared_ptr<OpenGLContext> openGLContext = m_openGLContextsFactories.value(factoryName)();
    openGLContext->setClearRed(clearRed);
    openGLContext->setClearGreen(clearGreen);
    openGLContext->setClearBlue(clearBlue);
    openGLContext->setClearAlpha(clearAlpha);
    openGLContext->setClearDepth(clearDepth);
    openGLContext->setDescription(description);
    openGLContext->setWindow(window);
    openGLContext->setEngine(m_engine);

    m_openGLContexts.insert(key, openGLContext);    // initOpenGLContext(openGLContext.get() );    

    return std::weak_ptr<OpenGLContext>(openGLContext);
}

int EngineContext::removeShape(const QString &key)
{
    return m_shapes.remove(key);
}

int EngineContext::removeLight(const QString &key)
{
    return m_lights.remove(key);
}

int EngineContext::removeScene(const QString &key)
{
    return m_scenes.remove(key);
}

int EngineContext::removeProgram(const QString &key)
{
    return m_programs.remove(key);
}

int EngineContext::removeEventsHandler(const QString &key)
{
    return m_eventsHandlers.remove(key);
}

int EngineContext::removeWindow(const QString &key)
{
    return m_windows.remove(key);
}

int EngineContext::removeOpenGLContext(const QString &key)
{
    return m_openGLContexts.remove(key);
}

int EngineContext::removeAllShapes()
{
    int size = m_shapes.size();
    m_shapes.clear();

    return size;
}

int EngineContext::removeAllLights()
{
    int size = m_lights.size();
    m_lights.clear();

    return size;
}

int EngineContext::removeAllScenes()
{
    int size = m_scenes.size();
    m_scenes.clear();

    return size;
}

int EngineContext::removeAllPrograms()
{
    int size = m_programs.size();
    m_programs.clear();

    return size;
}

int EngineContext::removeAllEventsHandlers()
{
    int size = m_eventsHandlers.size();
    m_eventsHandlers.clear();

    return size;
}

int EngineContext::removeAllWindows()
{
    int size = m_windows.size();
    m_windows.clear();;

    return size;
}

int EngineContext::removeAllOpenGLContexts()
{
    int size = m_openGLContexts.size();
    m_openGLContexts.clear();

    return size;
}

void EngineContext::removeAll()
{
    removeAllOpenGLContexts();
    removeAllWindows();
    removeAllEventsHandlers();
    removeAllScenes();
    removeAllShapes();
    removeAllLights();
    removeAllPrograms();
}

void EngineContext::setEngine(Engine *engine)
{
    m_engine = engine;
    ( !m_engine ) ? m_status |=  EngineContextStatus::NO_ENGINE
                  : m_status &= ~EngineContextStatus::NO_ENGINE;
}

std::weak_ptr<Shape> EngineContext::getShape(const QString &key) const
{
    return std::weak_ptr<Shape>(m_shapes[key]);
}

std::weak_ptr<Light> EngineContext::getLight(const QString &key) const
{
    return std::weak_ptr<Light>(m_lights[key]);
}

std::weak_ptr<Scene> EngineContext::getScene(const QString &key) const
{
    return std::weak_ptr<Scene>(m_scenes[key]);
}

std::weak_ptr<Program> EngineContext::getProgram(const QString &key) const
{
    return std::weak_ptr<Program>(m_programs[key]);
}

std::weak_ptr<EventsHandler> EngineContext::getEventsHandler(const QString &key) const
{
    return std::weak_ptr<EventsHandler>(m_eventsHandlers[key]);
}

std::weak_ptr<AppWindow> EngineContext::getWindow(const QString &key) const
{
    return std::weak_ptr<AppWindow>(m_windows[key]);
}

std::weak_ptr<OpenGLContext> EngineContext::getOpenGLContext(const QString &key) const
{
    return std::weak_ptr<OpenGLContext>(m_openGLContexts[key]);
}

QHash<QString, std::weak_ptr<Shape> > EngineContext::getAllShapes() const
{
    QHash<QString, std::weak_ptr<Shape> > weakShapes;
    for( QHash<QString, std::shared_ptr<Shape> >::const_iterator it = m_shapes.constBegin()
       ; it != m_shapes.constEnd()
       ; ++it )
    {
        weakShapes.insert(it.key(), std::weak_ptr<Shape>(it.value()));
    }

    return weakShapes;
}

QHash<QString, std::weak_ptr<Light> > EngineContext::getAllLights() const
{
    QHash<QString, std::weak_ptr<Light> > weakLights;
    for( QHash<QString, std::shared_ptr<Light> >::const_iterator it = m_lights.constBegin()
       ; it != m_lights.constEnd()
       ; ++it )
    {
        weakLights.insert(it.key(), std::weak_ptr<Light>(it.value()));
    }

    return weakLights;
}

QHash<QString, std::weak_ptr<Scene> > EngineContext::getAllScenes() const
{
    QHash<QString, std::weak_ptr<Scene> > weakScenes;
    for( QHash<QString, std::shared_ptr<Scene> >::const_iterator it = m_scenes.constBegin()
       ; it != m_scenes.constEnd()
       ; ++it )
    {
        weakScenes.insert(it.key(), std::weak_ptr<Scene>(it.value()));
    }

    return weakScenes;
}

QHash<QString, std::weak_ptr<Program> > EngineContext::getAllPrograms() const
{
    QHash<QString, std::weak_ptr<Program> > weakPrograms;
    for( QHash<QString, std::shared_ptr<Program> >::const_iterator it = m_programs.constBegin()
       ; it != m_programs.constEnd()
       ; ++it )
    {
        weakPrograms.insert(it.key(), std::weak_ptr<Program>(it.value()));
    }

    return weakPrograms;
}

QHash<QString, std::weak_ptr<EventsHandler> > EngineContext::getAllEventsHandlers() const
{
    QHash<QString, std::weak_ptr<EventsHandler> > weakHandlers;
    for( QHash<QString, std::shared_ptr<EventsHandler> >::const_iterator it = m_eventsHandlers.constBegin()
       ; it != m_eventsHandlers.constEnd()
       ; ++it )
    {
        weakHandlers.insert(it.key(), std::weak_ptr<EventsHandler>(it.value()));
    }

    return weakHandlers;
}

QHash<QString, std::weak_ptr<AppWindow> > EngineContext::getAllWindows() const
{
    QHash<QString, std::weak_ptr<AppWindow> > weakWindows;
    for( QHash<QString, std::shared_ptr<AppWindow> >::const_iterator it = m_windows.constBegin()
       ; it != m_windows.constEnd()
       ; ++it )
    {
        weakWindows.insert(it.key(), std::weak_ptr<AppWindow>(it.value()));
    }

    return weakWindows;
}

QHash<QString, std::weak_ptr<OpenGLContext> > EngineContext::getAllopenGLContexts() const
{
    QHash<QString, std::weak_ptr<OpenGLContext> > weakContexts;
    for( QHash<QString, std::shared_ptr<OpenGLContext> >::const_iterator it = m_openGLContexts.constBegin()
       ; it != m_openGLContexts.constEnd()
       ; ++it )
    {
        weakContexts.insert(it.key(), std::weak_ptr<OpenGLContext>(it.value()));
    }

    return weakContexts;
}

std::weak_ptr<Scene> EngineContext::getSelectedScene() noexcept(false)
{
    std::shared_ptr<Scene> selectedScene = m_selectedScene.lock();
    ( !selectedScene ) ? m_status |=  EngineContextStatus::INVALID_SELECTED_SCENE
                       : m_status &= ~EngineContextStatus::INVALID_SELECTED_SCENE;

    if( (m_status & EngineContextStatus::INVALID_SELECTED_SCENE) == EngineContextStatus::INVALID_SELECTED_SCENE )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    return m_selectedScene;
}

std::weak_ptr<AppWindow> EngineContext::getSelectedWindow() noexcept(false)
{
    std::shared_ptr<AppWindow> selectedWindow = m_selectedWindow.lock();
    ( !selectedWindow ) ? m_status |=  EngineContextStatus::INVALID_SELECTED_WINDOW
                        : m_status &= ~EngineContextStatus::INVALID_SELECTED_WINDOW;

    if( (m_status & EngineContextStatus::INVALID_SELECTED_WINDOW) == EngineContextStatus::INVALID_SELECTED_WINDOW )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    return m_selectedWindow;
}

std::weak_ptr<OpenGLContext> EngineContext::getSelectedOpenGLContext() noexcept(false)
{
    std::shared_ptr<OpenGLContext> selectedContext = m_selectedOpenGLContext.lock();
    ( !selectedContext ) ? m_status |=  EngineContextStatus::INVALID_SELECTED_OPENGL_CONTEXT
                         : m_status &= ~EngineContextStatus::INVALID_SELECTED_OPENGL_CONTEXT;

    if( (m_status & EngineContextStatus::INVALID_SELECTED_OPENGL_CONTEXT) == EngineContextStatus::INVALID_SELECTED_OPENGL_CONTEXT )
    {
        throw EngineContextException(this, "Engine context exception occured");
    }

    return m_selectedOpenGLContext;
}

bool EngineContext::selectScene(const QString &key)
{
    bool selected = false;
    const std::shared_ptr<Scene> scene = m_scenes.value(key);

    if( scene )
    {
        m_selectedScene = std::weak_ptr<Scene>(scene);
        selected = true;
    }

    return selected;
}

bool EngineContext::selectWindow(const QString &key)
{
    bool selected = false;
    const std::shared_ptr<AppWindow> window = m_windows.value(key);

    if( window )
    {
        m_selectedWindow = std::weak_ptr<AppWindow>(window);
        selected = true;
    }

    return selected;
}

bool EngineContext::selectOpenGLContext(const QString &key)
{
    bool selected = false;
    const std::shared_ptr<OpenGLContext> context = m_openGLContexts.value(key);

    if( context )
    {
        m_selectedOpenGLContext = std::weak_ptr<OpenGLContext>(context);
        selected = true;
    }

    return selected;
}

void EngineContext::registerShapeFactory(const QString &name, std::function<std::shared_ptr<Shape> ()> factory)
{
    m_shapesFactories.insert(name, factory);
}

void EngineContext::registerPointLightFactory(const QString &name, std::function<std::shared_ptr<PointLight> ()> factory)
{
    m_pointLightsFactories.insert(name, factory);
}

void EngineContext::registerDirectLightFactory(const QString &name, std::function<std::shared_ptr<DirectLight> ()> factory)
{
    m_directLightsFactories.insert(name, factory);
}

void EngineContext::registerSceneFactory(const QString &name, std::function<std::shared_ptr<Scene> ()> factory)
{
    m_scenesFactories.insert(name, factory);
}

void EngineContext::registerOpenGLContextFactory(const QString &name, std::function<std::shared_ptr<OpenGLContext> ()> factory)
{
    m_openGLContextsFactories.insert(name, factory);
}

void EngineContext::registerWindowFactory(const QString &name, std::function<std::shared_ptr<AppWindow> ()> factory)
{
    m_windowsFactories.insert(name, factory);
}

void EngineContext::registerProgramFactory(const QString &name, std::function<std::shared_ptr<Program> ()> factory)
{
    m_programsFactories.insert(name, factory);
}

void EngineContext::registerEventsHandlerFactory(const QString &name, std::function<std::shared_ptr<EventsHandler> ()> factory)
{
    m_eventsHandlersFactories.insert(name, factory);
}

void EngineContext::setDescription(const QString &description)
{
    m_description = description;
}

bool EngineContext::isSelectedOpenGLContextReady() const
{
    std::shared_ptr<OpenGLContext> context = m_selectedOpenGLContext.lock();

    bool ready = false;
    if( context )
    {
        ready = true;
    }

    if( ready )
    {
        ( context->isCreated() ) ? ready = true
                                 : ready = false;
    }

    return ready;
}
