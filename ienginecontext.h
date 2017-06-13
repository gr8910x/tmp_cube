#ifndef IENGINECONTEXT_H
#define IENGINECONTEXT_H

#include "commonincludings.h"

class Engine;
class Shape;
class Light;
class PointLight;
class DirectLight;
class Mesh;
class Scene;
class Renderer;
class Camera;
class Program;
class VertexShader;
class FragmentShader;
class EventsHandler;
class AppWindow;
class OpenGLContext;
class Texture;
class Vertex;
class Index;
class Transforms;

//! Interface for engine context implementation.
class IEngineContext
{
public:
    virtual std::weak_ptr<Shape> createShape( const QString                                 &factoryName    //! Creates new shape.
                                            , const QString                                 &key
                                            , const Mesh                                    &mesh
                                            , const Transforms                              &transforms
                                            , std::weak_ptr<Program>                         program
                                            , std::weak_ptr<Program>                         shadowProgram
                                            , const QHash<QString, std::weak_ptr<Texture> > &textures     = QHash<QString, std::weak_ptr<Texture> >()
                                            , const QString                                 &description  = "Empty description"
                                            ) noexcept(false) = 0;
    virtual std::weak_ptr<Shape> createShape( const QString                                 &factoryName    //! Creates new shape, overloaded function.
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
                                            , const QHash<QString, std::weak_ptr<Texture> > &textures         = QHash<QString, std::weak_ptr<Texture> >()
                                            , const QString                                 &meshDescription  = "Empty description"
                                            , const QString                                 &shapeDescription = "Empty description"
                                            ) noexcept(false) = 0;

    virtual std::weak_ptr<PointLight> createPointLight( const QString            &factoryName               //! Creates new light.
                                                      , const QString            &key
                                                      , const QVector4D          &lightColor
                                                      , GLfloat                   radius
                                                      , GLfloat                   intensity
                                                      , const Mesh               &mesh
                                                      , const Transforms         &transforms                                                     
                                                      , const QVector3D          &position
                                                      , std::weak_ptr<Program>    program   = std::weak_ptr<Program>()
                                                      , const QString           &description = "Empty description"
                                                      ) noexcept(false) = 0;

    virtual std::weak_ptr<DirectLight> createDirectLight( const QString          &factoryName               //! Creates new direct light.
                                                        , const QString          &key
                                                        , const QVector4D        &lightColor
                                                        , const QVector3D        &lightDirection
                                                        , const Camera           &shadowCamera
                                                        , GLfloat                 intensity
                                                        , std::weak_ptr<Program>  program     = std::weak_ptr<Program>()
                                                        , const QString          &description = "Empty description"
                                                        ) noexcept(false) = 0;

    virtual std::weak_ptr<Scene> createScene( const QString                      &factoryName               //! Creates new scene.
                                            , const QString                      &key
                                            , const Renderer                     &renderer
                                            , const Camera                       &camera
                                            , GLint                               x      = 0
                                            , GLint                               y      = 0
                                            , GLsizei                             width  = 640
                                            , GLsizei                             height = 480
                                            , const QList<std::weak_ptr<Shape> > &shapes = QList<std::weak_ptr<Shape> >()
                                            , const QList<std::weak_ptr<Light> > &lights = QList<std::weak_ptr<Light> >()
                                            , const QString                      &description = "Empty description"
                                            ) noexcept(false) = 0;
    virtual std::weak_ptr<Scene> createScene( const QString                      &factoryName               //! Creates new scene, overloaded function.
                                            , const QString                      &key
                                            , const Camera                       &camera
                                            , const QHash<com_defs::RendererPrograms::Programs, std::weak_ptr<Program> > &programs = QHash<com_defs::RendererPrograms::Programs, std::weak_ptr<Program> >()
                                            , GLint                               x      = 0
                                            , GLint                               y      = 0
                                            , GLsizei                             width  = 640
                                            , GLsizei                             height = 480
                                            , const QList<std::weak_ptr<Shape> > &shapes = QList<std::weak_ptr<Shape> >()
                                            , const QList<std::weak_ptr<Light> > &lights = QList<std::weak_ptr<Light> >()
                                            , const QString                      &rendererDescription = "Empty description"
                                            , const QString                      &sceneDescription    = "Empty description"
                                            ) noexcept(false) = 0;

    virtual std::weak_ptr<Program> createProgram( const QString                  &factoryName               //! Creates new program.
                                                , const QString                  &key
                                                , const VertexShader             &vertexShader
                                                , const FragmentShader           &fragmentShader
                                                , const QString                  &description = "Empty description"
                                                ) noexcept(false) = 0;
    virtual std::weak_ptr<Program> createProgram( const QString                  &factoryName               //! Creates new program, overloaded function.
                                                , const QString                  &key
                                                , const QString                  &vertexPath
                                                , const QString                  &fragmentPath
                                                , const QString                  &vertexDescription   = "Empty description"
                                                , const QString                  &fragmentDescription = "Empty description"
                                                , const QString                  &programDescription  = "Empty description"
                                                ) noexcept(false) = 0;

    virtual std::weak_ptr<EventsHandler> createEventsHandler( const QString      &factoryName               //! Creates new events handler.
                                                            , const QString      &key
                                                            , const QString      &description = "Empty description"
                                                            ) = 0;
    virtual std::weak_ptr<AppWindow> createWindow( const QString                 &factoryName               //! Creates new application window.
                                                 , const QString                 &key
                                                 , const QString                 &title
                                                 , std::weak_ptr<EventsHandler>   eventsHandler        = std::weak_ptr<EventsHandler>()
                                                 , int                            x      = SDL_WINDOWPOS_UNDEFINED
                                                 , int                            y      = SDL_WINDOWPOS_UNDEFINED
                                                 , int                            width  = 640
                                                 , int                            height = 480
                                                 , const QString                 &description = "Empty description"
                                                 , Uint32                         sdlWindowInitFlags   = SDL_WINDOW_SHOWN
                                                                                                       | SDL_WINDOW_OPENGL
                                                 , Uint32                         sdlRendererInitFlags = SDL_RENDERER_ACCELERATED
                                                                                                       | SDL_RENDERER_PRESENTVSYNC

                                                 ) noexcept(false) = 0;

    virtual std::weak_ptr<OpenGLContext> createOpenGLContext( const QString            &factoryName         //! Creates new OpenGL context.
                                                            , const QString            &key
                                                            , std::weak_ptr<AppWindow>  window
                                                            , const QVector4D          &clearColor   = QVector4D()
                                                            , GLfloat                   clearDepth   = 1.0f
                                                            , const QString            &description  = "Empty description"
                                                            ) noexcept(false) = 0;
    virtual std::weak_ptr<OpenGLContext> createOpenGLContext( const QString            &factoryName         //! Creates new OpenGL context, overloaded function.
                                                            , const QString            &key
                                                            , std::weak_ptr<AppWindow>  window
                                                            , GLfloat                   clearRed     = 0.0f
                                                            , GLfloat                   clearGreen   = 0.0f
                                                            , GLfloat                   clearBlue    = 0.0f
                                                            , GLfloat                   clearAlpha   = 0.0f
                                                            , GLfloat                   clearDepth   = 1.0f
                                                            , const QString            &description  = "Empty description"
                                                            ) noexcept(false) = 0;

    virtual int removeShape(const QString &key) = 0;                 //! Removes shape, returns 0 if shape with provided key doesn't exist.
    virtual int removeLight(const QString &key) = 0;                 //! Removes light, returns 0 if light with provided key doesn't exist.
    virtual int removeScene(const QString &key) = 0;                 //! Removes scene, returns 0 if scene with provided key doesn't exist.
    virtual int removeProgram(const QString &key) = 0;               //! Removes program, returns 0 if program with provided key doesn't exist.
    virtual int removeEventsHandler(const QString &key) = 0;         //! Removes events handler, returns 0 if handler with provided key doesn't exist.
    virtual int removeWindow(const QString &key) = 0;                //! Removes application window, returns 0 if window with provided key doesn't exist.
    virtual int removeOpenGLContext(const QString &key) = 0;         //! Removes OpenGL context, returns 0 if context with provided key doesn't exist.

    virtual int removeAllShapes() = 0;                               //! Removes all shapes, returns number of removed shapes.
    virtual int removeAllLights() = 0;                               //! Removes all lights, returns number of removed lights.
    virtual int removeAllScenes() = 0;                               //! Removes all scenes, returns number of removed scenes.
    virtual int removeAllPrograms() = 0;                             //! Removes all shading programs, returns number of removed programs.
    virtual int removeAllEventsHandlers() = 0;                       //! Removes all events handlers, returns number of removed events handlers.
    virtual int removeAllWindows() = 0;                              //! Removes all application windows, returns number of removed windows.
    virtual int removeAllOpenGLContexts() = 0;                       //! Removes all OpenGL contexts, returns number of removed OpenGL contexts.
    virtual void removeAll() = 0;                                    //! Removes all engine context elements.

    virtual std::weak_ptr<Shape> getShape(const QString &key) const = 0;     //! Returns pointer to shape with provided key.
    virtual std::weak_ptr<Light> getLight(const QString &key) const = 0;     //! Returns pointer to light with provided key.
    virtual std::weak_ptr<Scene> getScene(const QString &key) const = 0;     //! Returns pointer to scene with provided key.
    virtual std::weak_ptr<Program> getProgram(const QString &key) const = 0; //! Returns pointer to shading program with provided key.
    virtual std::weak_ptr<EventsHandler> getEventsHandler(const QString &key) const = 0;//! Returns pointer to events handler with provided key.
    virtual std::weak_ptr<AppWindow> getWindow(const QString &key) const = 0; //! Returns pointer to application window with provided key.
    virtual std::weak_ptr<OpenGLContext> getOpenGLContext(const QString &key) const = 0;//! Returns pointer to OpenGL context with provided key.

    virtual QHash<QString, std::weak_ptr<Shape> > getAllShapes() const = 0;  //! Returns all shapes.
    virtual QHash<QString, std::weak_ptr<Light> > getAllLights() const = 0;  //! Returns all lights.
    virtual QHash<QString, std::weak_ptr<Scene> > getAllScenes() const = 0;  //! Returns all scenes.
    virtual QHash<QString, std::weak_ptr<Program> > getAllPrograms() const = 0;//! Returns all shading programs.
    virtual QHash<QString, std::weak_ptr<EventsHandler> > getAllEventsHandlers() const = 0;//! Returns all events handlers.
    virtual QHash<QString, std::weak_ptr<AppWindow> > getAllWindows() const = 0;//! Returns all application windows.
    virtual QHash<QString, std::weak_ptr<OpenGLContext> > getAllopenGLContexts() const = 0;//! Returns all OpenGL contexts.

    virtual std::weak_ptr<Scene> getSelectedScene() noexcept(false) = 0;                //! Returns pointer to selected scene.
    virtual std::weak_ptr<AppWindow> getSelectedWindow() noexcept(false) = 0;           //! Returns pointer to selected applictation window.
    virtual std::weak_ptr<OpenGLContext> getSelectedOpenGLContext() noexcept(false) = 0;//! Returns pointer to selected OpenGL context.

    virtual bool selectScene(const QString &key) = 0;                 //! Selects scene for further operations, returns false if scene was not found.
    virtual bool selectWindow(const QString &key) = 0;                //! Selects application window for further operations, returns false if window was not found.
    virtual bool selectOpenGLContext(const QString &key) = 0;         //! Selects OpenGL context for further operations, returns false if context was not found.

    virtual void registerShapeFactory(const QString &name, std::function<std::shared_ptr<Shape> ()> factory) = 0;                 //! Registers shape factory.
    virtual void registerPointLightFactory(const QString &name, std::function<std::shared_ptr<PointLight> ()> factory) = 0;       //! Registers point light factory.
    virtual void registerDirectLightFactory(const QString &name, std::function<std::shared_ptr<DirectLight> ()> factory) = 0;     //! Registers direct light factory.
    virtual void registerSceneFactory(const QString &name, std::function<std::shared_ptr<Scene> ()> factory) = 0;                 //! Registers scene factory.
    virtual void registerOpenGLContextFactory(const QString &name, std::function<std::shared_ptr<OpenGLContext> ()> factory) = 0; //! Registers OpenGL context factory.
    virtual void registerWindowFactory(const QString &name, std::function<std::shared_ptr<AppWindow> () > factory) = 0;           //! Registers application window factory.
    virtual void registerProgramFactory(const QString &name, std::function<std::shared_ptr<Program> () > factory) = 0;            //! Registers shading program factory.
    virtual void registerEventsHandlerFactory(const QString &name, std::function<std::shared_ptr<EventsHandler> () > factory) = 0;//! Registers events handler factory.

    virtual const QHash<QString, std::function<std::shared_ptr<Shape> ()> > & getShapesFactories() const = 0;                     //! Returns shapes factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<PointLight> ()> > & getPointLightsFactories() const = 0;           //! Returns point lights factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<DirectLight> ()> > & getDirectLightsFactories() const = 0;         //! Returns direct lights factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<Scene> ()> > & getScenesFactories() const = 0;                     //! Returns scenes factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<OpenGLContext> () > > & getOpenGLContextsFactories() const = 0;    //! Returns OpenGL contexts factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<AppWindow> () > > & getWindowsFactories() const = 0;               //! Returns application windows factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<Program> () > > & getProgramsFactories() const = 0;                //! Returns shading programs factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<EventsHandler> () > > & getEventsHandlersFactories() const = 0;    //! Returns events handlers factories QHash.


    virtual ~IEngineContext() {}
};

#endif // IENGINECONTEXT_H
