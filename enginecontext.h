#ifndef ENGINECONTEXT_H
#define ENGINECONTEXT_H

#include "commonincludings.h"
#include "ienginecontext.h"

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

//! Contains, creates and removes context elements for application engine.
class EngineContext : public IEngineContext
{
public:
    EngineContext();                                                //! Default constructor.
    EngineContext( Engine        *engine                            //! Parameterized constructor.
                 , const QString &description = "Empty description" );

    EngineContext( const EngineContext &context );                  //! Copying constructor.

    virtual ~EngineContext() {}    

    const EngineContext & operator = (const EngineContext &context);//! Operator " =  ".

    virtual std::weak_ptr<Shape> createShape( const QString                                 &factoryName    //! Creates new shape.
                                            , const QString                                 &key
                                            , const Mesh                                    &mesh
                                            , const Transforms                              &transforms
                                            , std::weak_ptr<Program>                         program
                                            , std::weak_ptr<Program>                         shadowProgram
                                            , const QHash<QString, std::weak_ptr<Texture> > &textures     = QHash<QString, std::weak_ptr<Texture> >()
                                            , const QString                                 &description  = "Empty description"
                                            ) noexcept(false) override;
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
                                            ) noexcept(false) override;

    virtual std::weak_ptr<PointLight> createPointLight( const QString            &factoryName               //! Creates new point light.
                                                      , const QString            &key
                                                      , const QVector4D          &lightColor
                                                      , GLfloat                   radius
                                                      , GLfloat                   intensity
                                                      , const Mesh               &mesh
                                                      , const Transforms         &transforms                                                      
                                                      , const QVector3D          &position
                                                      , std::weak_ptr<Program>    program    = std::weak_ptr<Program>()
                                                      , const QString           &description = "Empty description"
                                                      ) noexcept(false) override;

    virtual std::weak_ptr<DirectLight> createDirectLight( const QString          &factoryName               //! Creates new direct light.
                                                        , const QString          &key
                                                        , const QVector4D        &lightColor
                                                        , const QVector3D        &lightDirection
                                                        , const Camera           &shadowCamera
                                                        , GLfloat                 intensity
                                                        , std::weak_ptr<Program>  program     = std::weak_ptr<Program>()
                                                        , const QString          &description = "Empty description"
                                                        ) noexcept(false) override;

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
                                            ) noexcept(false) override;
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
                                            ) noexcept(false) override;

    virtual std::weak_ptr<Program> createProgram( const QString                  &factoryName               //! Creates new program.
                                                , const QString                  &key
                                                , const VertexShader             &vertexShader
                                                , const FragmentShader           &fragmentShader
                                                , const QString                  &description = "Empty description"
                                                ) noexcept(false) override;
    virtual std::weak_ptr<Program> createProgram( const QString                  &factoryName               //! Creates new program, overloaded function.
                                                , const QString                  &key
                                                , const QString                  &vertexPath
                                                , const QString                  &fragmentPath
                                                , const QString                  &vertexDescription   = "Empty description"
                                                , const QString                  &fragmentDescription = "Empty description"
                                                , const QString                  &programDescription  = "Empty description"
                                                ) noexcept(false) override;

    virtual std::weak_ptr<EventsHandler> createEventsHandler( const QString      &factoryName               //! Creates new events handler.
                                                            , const QString      &key
                                                            , const QString      &description = "Empty description"
                                                            ) override;
    virtual std::weak_ptr<AppWindow> createWindow( const QString                 &factoryName
                                                 , const QString                 &key                       //! Creates new application window.
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

                                                 ) noexcept(false) override;

    virtual std::weak_ptr<OpenGLContext> createOpenGLContext( const QString            &factoryName         //! Creates new OpenGL context and sets it to provided window.
                                                            , const QString            &key
                                                            , std::weak_ptr<AppWindow>  window
                                                            , const QVector4D          &clearColor   = QVector4D()
                                                            , GLfloat                   clearDepth   = 1.0f
                                                            , const QString            &description  = "Empty description"
                                                            ) noexcept(false) override;
    virtual std::weak_ptr<OpenGLContext> createOpenGLContext( const QString            &factoryName         //! Creates new OpenGL context and sets it to provided window, overloaded function.
                                                            , const QString            &key
                                                            , std::weak_ptr<AppWindow>  window
                                                            , GLfloat                   clearRed     = 0.0f
                                                            , GLfloat                   clearGreen   = 0.0f
                                                            , GLfloat                   clearBlue    = 0.0f
                                                            , GLfloat                   clearAlpha   = 0.0f
                                                            , GLfloat                   clearDepth   = 1.0f
                                                            , const QString            &description  = "Empty description"
                                                            ) noexcept(false) override;

    virtual int removeShape(const QString &key) override;            //! Removes shape, returns 0 if shape with provided key doesn't exist.
    virtual int removeLight(const QString &key) override;            //! Removes light, returns 0 if light with provided key doesn't exist.
    virtual int removeScene(const QString &key) override;            //! Removes scene, returns 0 if scene with provided key doesn't exist.
    virtual int removeProgram(const QString &key) override;          //! Removes program, returns 0 if program with provided key doesn't exist.
    virtual int removeEventsHandler(const QString &key) override;    //! Removes events handler, returns 0 if handler with provided key doesn't exist.
    virtual int removeWindow(const QString &key) override;           //! Removes application window, returns 0 if window with provided key doesn't exist.
    virtual int removeOpenGLContext(const QString &key) override;    //! Removes OpenGL context, returns 0 if context with provided key doesn't exist.

    virtual int removeAllShapes() override;                          //! Removes all shapes, returns number of removed shapes.
    virtual int removeAllLights() override;                          //! Removes all lights, returns number of removed lights.
    virtual int removeAllScenes() override;                          //! Removes all scenes, returns number of removed scenes.
    virtual int removeAllPrograms() override;                        //! Removes all shading programs, returns number of removed programs.
    virtual int removeAllEventsHandlers() override;                  //! Removes all events handlers, returns number of removed events handlers.
    virtual int removeAllWindows() override;                         //! Removes all application windows, returns number of removed windows.
    virtual int removeAllOpenGLContexts() override;                  //! Removes all OpenGL contexts, returns number of removed OpenGL contexts.
    virtual void removeAll() override;                               //! Removes all engine context elements.

    virtual std::weak_ptr<Shape> getShape(const QString &key) const override;     //! Returns pointer to shape with provided key.
    virtual std::weak_ptr<Light> getLight(const QString &key) const override;     //! Returns pointer to light with provided key.
    virtual std::weak_ptr<Scene> getScene(const QString &key) const override;     //! Returns pointer to scene with provided key.
    virtual std::weak_ptr<Program> getProgram(const QString &key) const override; //! Returns pointer to shading program with provided key.
    virtual std::weak_ptr<EventsHandler> getEventsHandler(const QString &key) const override;//! Returns pointer to events handler with provided key.
    virtual std::weak_ptr<AppWindow> getWindow(const QString &key) const override;//! Returns pointer to application window with provided key.
    virtual std::weak_ptr<OpenGLContext> getOpenGLContext(const QString &key) const override;//! Returns pointer to OpenGL context with provided key.

    virtual QHash<QString, std::weak_ptr<Shape> > getAllShapes() const override;     //! Returns all shapes.
    virtual QHash<QString, std::weak_ptr<Light> > getAllLights() const override;     //! Returns all lights.
    virtual QHash<QString, std::weak_ptr<Scene> > getAllScenes() const override;     //! Returns all scenes.
    virtual QHash<QString, std::weak_ptr<Program> > getAllPrograms() const override; //! Returns all shading programs.
    virtual QHash<QString, std::weak_ptr<EventsHandler> > getAllEventsHandlers() const override;//! Returns all events handlers.
    virtual QHash<QString, std::weak_ptr<AppWindow> > getAllWindows() const override;//! Returns all application windows.
    virtual QHash<QString, std::weak_ptr<OpenGLContext> > getAllopenGLContexts() const override;//! Returns all OpenGL contexts.

    virtual std::weak_ptr<Scene> getSelectedScene() noexcept(false) override;                //! Returns pointer to selected scene.
    virtual std::weak_ptr<AppWindow> getSelectedWindow() noexcept(false) override;           //! Returns pointer to selected applictation window.
    virtual std::weak_ptr<OpenGLContext> getSelectedOpenGLContext() noexcept(false) override;//! Returns pointer to selected OpenGL context.

    virtual bool selectScene(const QString &key) override;           //! Selects scene for further operations, returns false if scene was not found.
    virtual bool selectWindow(const QString &key) override;          //! Selects application window for further operations, returns false if window was not found.
    virtual bool selectOpenGLContext(const QString &key) override;   //! Selects OpenGL context for further operations, returns false if context was not found.

    virtual void registerShapeFactory(const QString &name, std::function<std::shared_ptr<Shape> ()> factory) override;                 //! Registers shape factory.
    virtual void registerPointLightFactory(const QString &name, std::function<std::shared_ptr<PointLight> ()> factory) override;       //! Registers point light factory.
    virtual void registerDirectLightFactory(const QString &name, std::function<std::shared_ptr<DirectLight> ()> factory) override;     //! Registers direct light factory.
    virtual void registerSceneFactory(const QString &name, std::function<std::shared_ptr<Scene> ()> factory) override;                 //! Registers scene factory.
    virtual void registerOpenGLContextFactory(const QString &name, std::function<std::shared_ptr<OpenGLContext> ()> factory) override; //! Registers OpenGL context factory.
    virtual void registerWindowFactory(const QString &name, std::function<std::shared_ptr<AppWindow> () > factory) override;           //! Registers application window factory.
    virtual void registerProgramFactory(const QString &name, std::function<std::shared_ptr<Program> () > factory) override;            //! Registers shading program factory.
    virtual void registerEventsHandlerFactory(const QString &name, std::function<std::shared_ptr<EventsHandler> () > factory) override;//! Registers events handler factory.

    virtual const QHash<QString, std::function<std::shared_ptr<Shape> ()> > & getShapesFactories() const override { return m_shapesFactories; }                          //! Returns shapes factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<PointLight> ()> > & getPointLightsFactories() const override { return m_pointLightsFactories; }           //! Returns point lights factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<DirectLight> ()> > & getDirectLightsFactories() const override { return m_directLightsFactories; }        //! Returns direct lights factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<Scene> ()> > & getScenesFactories() const override { return m_scenesFactories; }                          //! Returns scenes factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<OpenGLContext> () > > & getOpenGLContextsFactories() const override { return m_openGLContextsFactories; } //! Returns OpenGL contexts factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<AppWindow> () > > & getWindowsFactories() const override { return m_windowsFactories; }                   //! Returns application windows factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<Program> () > > & getProgramsFactories() const override { return m_programsFactories; }                   //! Returns shading programs factories QHash.
    virtual const QHash<QString, std::function<std::shared_ptr<EventsHandler> () > > & getEventsHandlersFactories() const override { return m_eventsHandlersFactories; } //! Returns events handlers factories QHash.

public:
    const Engine * getEngine() const { return m_engine; }            //! Returns pointer to engine object.
    Engine * getEngine() { return m_engine; }                        //! Returns pointer to engine object, overloaded function.
    void setEngine(Engine * engine);                                 //! Sets pointer to engine object.    

    const QString & getDescription() const { return m_description;}  //! Returns engine context description.
    void setDescription(const QString &description);                 //! Sets engine context description.

    uint getName() const { return m_name; }                          //! Returns autogenerated engine context name.
    uint getStatus() const { return m_status; }                      //! Returns engine context status bitmask.

    bool isSelectedOpenGLContextReady() const;                       //! Returns true if selected OpenGL context is ready to operate.

public:
    static uint getCounter() { return counter; }                     //! Returns number of created engine context objects.

protected:
    void setStatus(uint status) { m_status = status; }               //! Sets engine context status bitmask.

    const QHash<QString, std::shared_ptr<Shape> > & getShapes() const { return m_shapes; }                                               //! Returns engine shapes.
    const QHash<QString, std::shared_ptr<Light> > & getLights() const { return m_lights; }                                               //! Returns engine lights.
    const QHash<QString, std::shared_ptr<Scene> > & getScenes() const { return m_scenes; }                                               //! Returns engine scenes.
    const QHash<QString, std::shared_ptr<Program> > & getPrograms() const { return m_programs; }                                         //! Returns engine shading programs.
    const QHash<QString, std::shared_ptr<EventsHandler> > & getEventsHandlers() const { return m_eventsHandlers; }                       //! Returns engine events handlers.
    const QHash<QString, std::shared_ptr<AppWindow> > & getWindows() const { return m_windows; }                                         //! Returns engine application windows.
    const QHash<QString, std::shared_ptr<OpenGLContext> > & getOpenGLContexts() const { return m_openGLContexts; }                       //! Returns engine OpenGL contexts.
    QHash<QString, std::shared_ptr<Shape> > & getShapes() { return m_shapes; }                                                           //! Returns engine shapes, overloaded function.
    QHash<QString, std::shared_ptr<Light> > & getLights() { return m_lights; }                                                           //! Returns engine lights, overloaded function.
    QHash<QString, std::shared_ptr<Scene> > & getScenes() { return m_scenes; }                                                           //! Returns engine scenes, overloaded function.
    QHash<QString, std::shared_ptr<Program> > & getPrograms() { return m_programs; }                                                     //! Returns engine shading programs, overloaded function.
    QHash<QString, std::shared_ptr<EventsHandler> > & getEventsHandlers() { return m_eventsHandlers; }                                   //! Returns engine events handlers, overloaded function.
    QHash<QString, std::shared_ptr<AppWindow> > & getWindows() { return m_windows; }                                                     //! Returns engine application windows, overloaded function.
    QHash<QString, std::shared_ptr<OpenGLContext> > & getOpenGLContexts() { return m_openGLContexts; }                                   //! Returns engine OpenGL contexts, overloaded function.
    void setShapes(const QHash<QString, std::shared_ptr<Shape> > &shapes) { m_shapes = shapes; }                                         //! Sets engine shapes.
    void setLights(const QHash<QString, std::shared_ptr<Light> > &lights) { m_lights = lights; }                                         //! Sets engine lights.
    void setScenes(const QHash<QString, std::shared_ptr<Scene> > &scenes) { m_scenes = scenes; }                                         //! Sets engine scenes.
    void setPrograms(const QHash<QString, std::shared_ptr<Program> > &programs) { m_programs = programs; }                               //! Sets engine shading programs.
    void setEventsHandlers(const QHash<QString, std::shared_ptr<EventsHandler> > &eventsHandlers) { m_eventsHandlers = eventsHandlers; } //! Sets engine events handlers.
    void setWindows(const QHash<QString, std::shared_ptr<AppWindow> > &windows) { m_windows = windows; }                                 //! Sets engine application windows.
    void setOpenGLContexts(const QHash<QString, std::shared_ptr<OpenGLContext> > &openGLContexts) { m_openGLContexts = openGLContexts; } //! Sets engine OpenGL contexts.

    QHash<QString, std::function<std::shared_ptr<Shape> ()> > & getShapesFactories() { return m_shapesFactories; }                                                                             //! Returns shapes factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<PointLight> ()> > & getPointLightsFactories() { return m_pointLightsFactories; }                                                              //! Returns point lights factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<DirectLight> ()> > & getDirectLightsFactories() { return m_directLightsFactories; }                                                           //! Returns direct lights factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<Scene> ()> > & getScenesFactories() { return m_scenesFactories; }                                                                             //! Returns scenes factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<OpenGLContext> () > > & getOpenGLContextsFactories() { return m_openGLContextsFactories; }                                                    //! Returns OpenGL contexts factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<AppWindow> () > > & getWindowsFactories() { return m_windowsFactories; }                                                                      //! Returns application windows factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<Program> () > > & getProgramsFactories() { return m_programsFactories; }                                                                      //! Returns shading programs factories QHash, overloaded function.
    QHash<QString, std::function<std::shared_ptr<EventsHandler> () > > & getEventsHandlersFactories() { return m_eventsHandlersFactories; }                                                    //! Returns events handlers factories QHash, overloaded function.
    void setShapesFactories(const QHash<QString, std::function<std::shared_ptr<Shape> ()> > &shapesFactories) { m_shapesFactories = shapesFactories; }                                         //! Sets shapes factories QHash.
    void setPointLightsFactories(const QHash<QString, std::function<std::shared_ptr<PointLight> ()> > &pointLightsFactories) { m_pointLightsFactories = pointLightsFactories; }                //! Sets point lights factories QHash.
    void setDirectLightsFactories(const QHash<QString, std::function<std::shared_ptr<DirectLight> ()> > &directLightsFactories) { m_directLightsFactories = directLightsFactories; }           //! Sets direct lights factories QHash.
    void setScenesFactories(const QHash<QString, std::function<std::shared_ptr<Scene> ()> > &scenesFactories) { m_scenesFactories = scenesFactories; }                                         //! Sets scenes factories QHash.
    void setOpenGLContextsFactories(const QHash<QString, std::function<std::shared_ptr<OpenGLContext> () > > &openGLContextsFactories) { m_openGLContextsFactories = openGLContextsFactories; }//! Sets OpenGL contexts factories QHash.
    void setWindowsFactories(const QHash<QString, std::function<std::shared_ptr<AppWindow> () > > &windowsFactories) { m_windowsFactories = windowsFactories; }                                //! Sets application windows factories QHash.
    void setProgramsFactories(const QHash<QString, std::function<std::shared_ptr<Program> () > > &programsFactories) { m_programsFactories = programsFactories; }                              //! Sets shading programs factories QHash.
    void setEventsHandlersFactories(const QHash<QString, std::function<std::shared_ptr<EventsHandler> () > > &eventsHandlersFactories) { m_eventsHandlersFactories = eventsHandlersFactories; }//! Sets events handlers factories QHash.

private:
    static uint counter;            //! Counter of created engine context objects.

private:
    Engine *                                        m_engine;        //! Pointer to engine object.

    QHash<QString, std::shared_ptr<Shape> >         m_shapes;        //! Engine shapes.
    QHash<QString, std::shared_ptr<Light> >         m_lights;        //! Engine lights.
    QHash<QString, std::shared_ptr<Scene> >         m_scenes;        //! Engine scenes.
    QHash<QString, std::shared_ptr<Program> >       m_programs;      //! Engine shading programs.
    QHash<QString, std::shared_ptr<EventsHandler> > m_eventsHandlers;//! Engine events handlers.
    QHash<QString, std::shared_ptr<AppWindow> >     m_windows;       //! Engine application windows.
    QHash<QString, std::shared_ptr<OpenGLContext> > m_openGLContexts;//! Engine OpenGL contexts.

    QHash<QString, std::function<std::shared_ptr<Shape> ()> >         m_shapesFactories;         //! Shapes factories QHash.
    QHash<QString, std::function<std::shared_ptr<PointLight> ()> >    m_pointLightsFactories;    //! Point lights factories QHash.
    QHash<QString, std::function<std::shared_ptr<DirectLight> ()> >   m_directLightsFactories;   //! Direct lights factories QHash.
    QHash<QString, std::function<std::shared_ptr<Scene> ()> >         m_scenesFactories;         //! Scenes factories QHash.
    QHash<QString, std::function<std::shared_ptr<OpenGLContext> ()> > m_openGLContextsFactories; //! OpenGL contexts factories QHash.
    QHash<QString, std::function<std::shared_ptr<AppWindow> () > >    m_windowsFactories;        //! Application windows factories QHash.
    QHash<QString, std::function<std::shared_ptr<Program> () > >      m_programsFactories;       //! Shading programs factories QHash.
    QHash<QString, std::function<std::shared_ptr<EventsHandler> () > >m_eventsHandlersFactories; //! Events handlers factories QHash.

    std::weak_ptr<Scene>                            m_selectedScene;        //! Selected scene pointer.
    std::weak_ptr<AppWindow>                        m_selectedWindow;       //! Selected application window pointer.
    std::weak_ptr<OpenGLContext>                    m_selectedOpenGLContext;//! Selected OpenGL context pointer.

    QString      m_description;     //! Description of engine context.

    uint         m_name;            //! Autogenerated engine context name.
    uint         m_status;          //! Engine context status bitmask.
};

#endif // ENGINECONTEXT_H
