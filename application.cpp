#include "application.h"
#include "engine.h"
#include "appwindow.h"
#include "camera.h"
#include "enginecontext.h"
#include "fragmentshader.h"
#include "vertexshader.h"
#include "program.h"
#include "eventshandler.h"
#include "mesh.h"
#include "vertex.h"
#include "index.h"
#include "openglcontext.h"
#include "renderer.h"
#include "rendertarget.h"
#include "shape.h"
#include "light.h"
#include "pointlight.h"
#include "directlight.h"
#include "scene.h"
#include "texture.h"
#include "transforms.h"
#include "commonshapes.h"

using namespace com_defs;

uint Application::counter = 0;

Application::Application( const QString &description ) :
    m_description ( description )
{
    m_name = ++ Application::counter;
}

Application::Application( const Application &application ) :
    m_name        ( application.m_name        ),
    m_description ( application.m_description )
{
}

const Application & Application::operator = (const Application &application)
{
    m_description    = application.m_description;

    return *this;
}

Application & Application::operator() () noexcept(false)
{
    run();

    return *this;
}

void Application::setDescription(const QString &description)
{
    m_description = description;
}

void Application::run() noexcept(false)
{
    std::cout << "Application started." << std::endl;

    Engine  engine("Application engine");// Creating engine object.
    engine.init();                       // Initializing engine.

    engine.getContext().registerEventsHandlerFactory( "eventsHandlersFactoryOne"    // Registering events handlers factory.
                                                    , &EventsHandler::createObject );
    engine.getContext().registerOpenGLContextFactory( "openGLContextsFactoryOne"    // Registering OpenGL contexts factory.
                                                    , &OpenGLContext::createObject );
    engine.getContext().registerProgramFactory( "programsFactoryOne"                // Registering programs factory.
                                              , &Program::createObject );
    engine.getContext().registerSceneFactory( "scenesFactoryOne"                    // Registering scenes factory.
                                            , &Scene::createObject );
    engine.getContext().registerShapeFactory( "shapesFactoryOne"                    // Registering shapes factory.
                                            , &Shape::createObject );
    engine.getContext().registerWindowFactory( "windowsFactoryOne"                  // Registering windows factory.
                                             , &AppWindow::createObject );
    engine.getContext().registerPointLightFactory( "pointLightsFactoryOne"          // Registering point lights factory.
                                                 , &PointLight::createObject );
    engine.getContext().registerDirectLightFactory( "directLightsFactoryOne"        // Registering direct lights factory.
                                                  , &DirectLight::createObject );

    std::weak_ptr<EventsHandler> weakEventsHandlerOne = engine.getContext().createEventsHandler( "eventsHandlersFactoryOne" // Creating events handler one.
                                                                                               , "eventsHandlerOne"
                                                                                               , "Main events handler");
    std::weak_ptr<AppWindow>     weakWindowOne        = engine.getContext().createWindow( "windowsFactoryOne"               // Creating application window one.
                                                                                        , "windowOne"
                                                                                        , "OpenGL SDL scene"
                                                                                        , weakEventsHandlerOne );
    engine.getContext().createOpenGLContext( "openGLContextsFactoryOne"     // Creating OpenGL context.
                                           , "openGLContextOne"
                                           , weakWindowOne
                                           , { 0.859f, 0.549f, 1.0f, 0.0f }
                                           , 1.0f
                                           , "OpenGL context One" );
    engine.getContext().selectWindow("windowOne");   // Selecting active window.
    engine.getContext().selectOpenGLContext("openGLContextOne"); // Selecting active OpenGL context.


    std::shared_ptr<AppWindow> selectedWindow = engine.getContext().getSelectedWindow().lock(); // Receiving active window.
    std::shared_ptr<OpenGLContext> selectedOpenGLContext = engine.getContext().getSelectedOpenGLContext().lock(); // Receiving active OpenGL context.


    selectedWindow->setOpenGLContext(std::weak_ptr<OpenGLContext>(selectedOpenGLContext) ); // Setting OpenGL context to selected window.
    selectedWindow->create();           // Initializing window.
    selectedOpenGLContext->create();    // Initializing OpenGL context.

    Mesh cubeMeshOne( com_shapes::cube( {0.5529f, 0.1725f, 0.5686f, 1.0f}
                                      , "Cube mesh one")
                    );
    Transforms cubeTransformsOne( {-4.0f,  0.0f,  0.0f }        // Translation transformation.
                                , { 0.0f,  0.0f,  0.0f,  0.0f } // Rotation transformation.
                                , { 1.0f,  1.0f,  1.0f }        // Scaling transformation.
                                );
    std::weak_ptr<Program> weakCubeProgramOne = engine.getContext().createProgram( "programsFactoryOne"         // Creating cube shading program.
                                                                                 , "cubeProgramOne"             // Program key.
                                                                                 , "shaders/vertex/shape.vsh"   // Vertex shader path.
                                                                                 , "shaders/fragment/shape.fsh" // Fragment shader path.
                                                                                 , "Shape vertex shader"        // Vertex shader description.
                                                                                 , "Shape fragment shader"      // Fragment shader description.
                                                                                 , "Cube program one"           // Program description.
                                                                                 );
    std::shared_ptr<Program> cubeProgramOne = weakCubeProgramOne.lock();
    cubeProgramOne->create();   // Initializing program.
    cubeProgramOne->link();     // Linking program.

    std::weak_ptr<Program> weakShadowProgramOne = engine.getContext().createProgram( "programsFactoryOne"         // Creating shadow shading program.
                                                                                   , "shadowProgramOne"           // Program key.
                                                                                   , "shaders/vertex/shadow.vsh"  // Vertex shader path.
                                                                                   , "shaders/fragment/shadow.fsh"// Fragment shader path.
                                                                                   , "Shadow vertex shader"       // Vertex shader description.
                                                                                   , "Shadow fragment shader"     // Fragment shader description.
                                                                                   , "Shadow program one"         // Program description.
                                                                                   );
    std::shared_ptr<Program> shadowProgramOne = weakShadowProgramOne.lock();
    shadowProgramOne->create();   // Initializing program.
    shadowProgramOne->link();     // Linking program.

    std::weak_ptr<Shape> weakCubeOne = engine.getContext().createShape( "shapesFactoryOne"    // Creating cube one shape.
                                                                      , "cubeOne"             //
                                                                      , cubeMeshOne           // Shape mesh.
                                                                      , cubeTransformsOne     // Shape transforms.
                                                                      , weakCubeProgramOne    // Shape shading program.
                                                                      , weakShadowProgramOne  // Shadow program.
                                                                      );
    std::shared_ptr<Shape> cubeOne = weakCubeOne.lock();
    cubeOne->getMesh().genBuffers();    // Generating shape buffers.
    cubeOne->getMesh().pushData();      // Pushing data to OpenGL context.

    Transforms cubeTransformsTwo( { 4.0f,  0.0f,  0.0f }         // Translation transformation.
                                , { 0.0f,  0.0f,  0.0f,  0.0f }  // Rotation transformation.
                                , { 1.0f,  1.0f,  1.0f }         // Scaling transformation.
                                );
    std::weak_ptr<Shape> weakCubeTwo = engine.getContext().createShape( "shapesFactoryOne"    // Creating cube two shape.
                                                                      , "cubeTwo"             // Shape key.
                                                                      , cubeMeshOne           // Shape mesh.
                                                                      , cubeTransformsTwo     // Shape transforms.
                                                                      , weakCubeProgramOne    // Shape shading program.
                                                                      , weakShadowProgramOne  // Shadow program.
                                                                      );
    std::shared_ptr<Shape> cubeTwo = weakCubeTwo.lock();
    cubeTwo->getMesh().genBuffers();    // Generating shape buffers.
    cubeTwo->getMesh().pushData();      // Pushing data to OpenGL context.

    Transforms cubeTransformsThree( { 0.0f,  0.0f,  0.0f }       // Translation transformation.
                                  , { 0.0f,  0.0f,  0.0f,  0.0f }// Rotation transformation.
                                  , { 1.0f,  1.0f,  1.0f }       // Scaling transformation.
                                  );
    std::weak_ptr<Shape> weakCubeThree = engine.getContext().createShape( "shapesFactoryOne"    // Creating cube two shape.
                                                                        , "cubeThree"           // Shape key.
                                                                        , cubeMeshOne           // Shape mesh.
                                                                        , cubeTransformsThree   // Shape transforms.
                                                                        , weakCubeProgramOne    // Shape shading program.
                                                                        , weakShadowProgramOne  // Shadow program.
                                                                        );
    std::shared_ptr<Shape> cubeThree = weakCubeThree.lock();
    cubeThree->getMesh().genBuffers();  // Generating shape buffers.
    cubeThree->getMesh().pushData();    // Pushing data to OpenGL context.


    Mesh squareMeshOne( com_shapes::square( {0.8862f, 0.8275f, 0.9490f, 1.0f}
                                          , "Square mesh one")
                      );
    Transforms squareTransformsOne( { 0.0f,  0.0f,-10.0f }       // Translation transformation.
                                  , { 0.0f,  0.0f,  0.0f, 0.0f } // Rotation transformation.
                                  , {20.0f, 12.0f,  1.0f }       // Scaling transformation.
                                  );
    std::weak_ptr<Shape> weakSquareOne = engine.getContext().createShape( "shapesFactoryOne"  // Creating square one shape.
                                                                        , "squareOne"         // Shape key.
                                                                        , squareMeshOne       // Shape mesh.
                                                                        , squareTransformsOne // Shape transforms.
                                                                        , weakCubeProgramOne  // Shape shading program.
                                                                        , weakShadowProgramOne// Shadow program.
                                                                        );
    std::shared_ptr<Shape> squareOne = weakSquareOne.lock();
    squareOne->getMesh().genBuffers();  // Generating square buffers.
    squareOne->getMesh().pushData();    // Pushing data to OpenGL context.


    std::weak_ptr<Program> weakPointLigthProgramOne = engine.getContext().createProgram( "programsFactoryOne"              // Creating point light shading program.
                                                                                       , "pointLigthProgramOne"            // Program key.
                                                                                       , "shaders/vertex/pointLight.vsh"   // Vertex shader path.
                                                                                       , "shaders/fragment/pointLight.fsh" // Fragment shader path.
                                                                                       , "Point light vertex shader"       // Vertex shader description.
                                                                                       , "Point light fragment shader"     // Fragment shader description.
                                                                                       , "Point light program one"         // Program description.
                                                                                       );
    std::shared_ptr<Program> pointLigthProgramOne = weakPointLigthProgramOne.lock();
    pointLigthProgramOne->create();     // Creating program.
    pointLigthProgramOne->link();       // Linking program.
    Transforms pointLightTransformsOne( { 0.0f,  5.0f,  0.0f }       // Translation transformation.
                                      , { 0.0f,  0.0f,  0.0f,  0.0f }// Rotation transformation.
                                      , { 1.0f,  1.0f,  1.0f }       // Scaling transformation.
                                      );
    Mesh pointLightMeshOne( com_shapes::sphere( 3                           // Recursion level.
                                              , { 1.0f, 1.0f, 1.0f, 1.0f}   // Light color.
                                              , "Point light mesh one")     // Mesh description.
                          );
    std::weak_ptr<PointLight> weakPointLightOne = engine.getContext().createPointLight( "pointLightsFactoryOne"         // Creating point light.
                                                                                      , "pointLightOne"                 // Point light key.
                                                                                      , { 1.0f,  1.0f,  1.0f,  1.0f }   // Light color.
                                                                                      , 7.5f                            // Light radius.
                                                                                      , 0.25f                           // Light intensity.
                                                                                      , pointLightMeshOne               // Light mesh.
                                                                                      , pointLightTransformsOne         // Light transforms.                                                                                     
                                                                                      , { 0.0f,  0.0f,  0.0f }          // Light position.
                                                                                      , weakPointLigthProgramOne        // Light shading program.
                                                                                      , "Point light one"               // Light description.
                                                                                      );
    std::shared_ptr<PointLight> pointLightOne = weakPointLightOne.lock();
    pointLightOne->getMesh().genBuffers();  // Generating point light buffers.
    pointLightOne->getMesh().pushData();    // Pushing data to OpenGL context.

    Transforms pointLightTransformsTwo( { 0.0f, -5.0f,  0.0f }       // Translation transformation.
                                      , { 0.0f,  0.0f,  0.0f,  0.0f }// Rotation transformation.
                                      , { 1.0f,  1.0f,  1.0f }       // Scaling transformation.
                                      );
    std::weak_ptr<PointLight> weakPointLightTwo = engine.getContext().createPointLight( "pointLightsFactoryOne"         // Creating point light.
                                                                                      , "pointLightTwo"                 // Point light key.
                                                                                      , { 0.788f, 0.702f, 0.949f, 1.0f }// Light color.
                                                                                      , 7.5f                            // Light radius.
                                                                                      , 0.25f                           // Light intensity.
                                                                                      , pointLightMeshOne               // Light mesh.
                                                                                      , pointLightTransformsTwo         // Light transforms.
                                                                                      , { 0.0f, 0.0f, 0.0f }            // Light position.
                                                                                      , weakPointLigthProgramOne        // Light shading program.
                                                                                      , "Point light two"               // Light description.
                                                                                      );
    std::shared_ptr<PointLight> pointLightTwo = weakPointLightTwo.lock();
    pointLightTwo->getMesh().genBuffers();  // Generating point light buffers.
    pointLightTwo->getMesh().pushData();    // Pushing data to OpenGL context.


    std::weak_ptr<Program> weakDirectLightProgramOne = engine.getContext().createProgram( "programsFactoryOne"                      // Creating direct light shading program.
                                                                                        , "directLightProgramOne"                   // Program key.
                                                                                        , "shaders/vertex/directLight.vsh"          // Vertex shader path.
                                                                                        , "shaders/fragment/directLight.fsh"        // Fragment shader path.
                                                                                        , "Direct light vertex shader"              // Vertex shader description.
                                                                                        , "Direct light fragment shader"            // Fragment shader description.
                                                                                        , "Direct light program one"                // Program description.
                                                                                        );
    std::shared_ptr<Program> directLightProgramOne = weakDirectLightProgramOne.lock();
    directLightProgramOne->create();  // Creating program.
    directLightProgramOne->link();    // Linking program.

    Camera directLightShadowCameraOne( 100.0f                           // FOVY (Y axis angle).
                                     , 640.0f                           // Width.
                                     , 480.0f                           // Height.
                                     , 0.1f                             // Distance to near separation plane.
                                     , 100.0f                           // Distance to far separation plane.
                                     , { 0.0f,  0.0f,  1.0f }           // Camera position.
                                     , { 0.0f,  0.0f,  0.0f }           // Camera gaze point.
                                     , { 0.0f,  1.0f,  0.0f }           // Camera upper direction.
                                     , CameraMode::ORTHOGRAPHIC         // Projection mode.
                                     , "Direct light shadow camera one" // Camera description.
                                     );
    std::weak_ptr<DirectLight> weakDirectLightOne = engine.getContext().createDirectLight( "directLightsFactoryOne"                 // Creating direct light.
                                                                                         , "directLightOne"                         // Direct light key.
                                                                                         , { 1.0f, 1.0f, 1.0f, 1.0f }               // Light color.
                                                                                         , { 1.0f, 0.0f,-1.5f }                     // Light direction.
                                                                                         , directLightShadowCameraOne               // Shadow camera.
                                                                                         , 0.25f                                    // Light intensity.
                                                                                         , weakDirectLightProgramOne                // Light shading program.
                                                                                         , "Direct light one"                       // Light description.
                                                                                         );


    std::weak_ptr<Program> weakTexture2DRendererProgramOne = engine.getContext().createProgram( "programsFactoryOne"                     // Creating 2D texture renderer shading program.
                                                                                              , "texture2DRendererProgramOne"            // Program key.
                                                                                              , "shaders/vertex/texture2DRenderer.vsh"   // Vertex shader path.
                                                                                              , "shaders/fragment/texture2DRenderer.fsh" // Fragment shader path.
                                                                                              , "2D texture renderer vertex shader"      // Vertex shader description.
                                                                                              , "2D texture renderer fragment shader"    // Fragment shader description.
                                                                                              , "2D texture renderer program one"        // Program description.
                                                                                              );
    std::shared_ptr<Program> texture2DRendererProgramOne = weakTexture2DRendererProgramOne.lock();
    texture2DRendererProgramOne->create();  // Creating program.
    texture2DRendererProgramOne->link();    // Linking program.


    std::weak_ptr<Program> weakLightCombinerProgramOne = engine.getContext().createProgram( "programsFactoryOne"                       // Creating light combiner shading program.
                                                                                          , "lightCombinerProgramOne"                  // Program key.
                                                                                          , "shaders/vertex/lightCombiner.vsh"         // Vertex shader path.
                                                                                          , "shaders/fragment/lightCombiner.fsh"       // Fragment shader path.
                                                                                          , "Light combiner vertex shader"             // Vertex shader description.
                                                                                          , "Light combiner fragment shader"           // Fragment shader description.
                                                                                          , "Light combiner program one"               // Program description.
                                                                                          );
    std::shared_ptr<Program> lightCombinerProgramOne = weakLightCombinerProgramOne.lock();
    lightCombinerProgramOne->create();  // Creating program.
    lightCombinerProgramOne->link();    // Linking program.


    std::weak_ptr<Program> weakBlurRangeProgramOne = engine.getContext().createProgram( "programsFactoryOne"                           // Creating blur range shading program.
                                                                                      , "blurRangeProgramOne"                          // Program key.
                                                                                      , "shaders/vertex/blurRange.vsh"                 // Vertex shader path.
                                                                                      , "shaders/fragment/blurRange.fsh"               // Fragments shader path.
                                                                                      , "Blur range vertex shader"                     // Vertex shader description.
                                                                                      , "Blur range fragment shader"                   // Fragment shader description.
                                                                                      , "Blur range program one"                       // Program description.
                                                                                      );
    std::shared_ptr<Program> blurRangeProgramOne = weakBlurRangeProgramOne.lock();
    blurRangeProgramOne->create();   // Creating program.
    blurRangeProgramOne->link();     // Linking program.


    Camera cameraOne( 100.0f                    // FOVY (Y axis angle).
                    , 640.0f                    // Width.
                    , 480.0f                    // Height.
                    , 0.1f                      // Distance to near separation plane.
                    , 100.0f                    // Distance to far separation plane.
                    , { 0.0f,  3.0f,  9.0f }    // Camera position.
                    , { 0.0f,  0.0f,  0.0f }    // Camera gaze point.
                    , { 0.0f,  9.0f, -3.0f }    // Camera upper direction.
                    , CameraMode::PERSPECTIVE   // Projection mode.
                    , "Camera one"              // Camera description.
                    );
    std::weak_ptr<Scene> weakSceneOne = engine.getContext().createScene( "scenesFactoryOne"     // Creating and initializing scene one.
                                                                       , "sceneOne"             // Scene key.
                                                                       , cameraOne              // Scene camera.
                                                                       , { { RendererPrograms::TEXTURE_2D_RENDERER, weakTexture2DRendererProgramOne } // Scene renderer programs QHash.
                                                                         , { RendererPrograms::LIGHT_COMBINER,      weakLightCombinerProgramOne     }
                                                                         , { RendererPrograms::BLUR_RANGER,         weakBlurRangeProgramOne         }
                                                                         }
                                                                       , 0                      // Scene bottom-left x coordinate of viewport.
                                                                       , 0                      // Scene bottom-left y coordinate of viewport.
                                                                       , 640                    // Width of viewport.
                                                                       , 480                    // Height of viewport.
                                                                       , { weakSquareOne              // Scene shapes.
                                                                         , weakCubeTwo
                                                                         , weakCubeThree
                                                                         , weakCubeOne
                                                                         }
                                                                       , { //weakPointLightOne        // Scene lights.
                                                                          //weakPointLightTwo
                                                                          weakDirectLightOne
                                                                         }
                                                                       , "Scene one renderer"   // Scene renderer description.
                                                                       , "Scene one"            // Scene description.
                                                                       );

    engine.getContext().selectScene("sceneOne");    // Selecting active scene.
    std::shared_ptr<Scene> selectedScene = engine.getContext().getSelectedScene().lock();// Receiving active scene.

    selectedScene->getRenderer().genBuffers();  //   Generating scene renderer buffers.


    selectedWindow->run();  // Running selected application window.


    engine.getName();

}
