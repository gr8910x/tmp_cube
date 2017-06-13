#include "renderer.h"
#include "rendererexception.h"
#include "scene.h"
#include "shape.h"
#include "light.h"
#include "pointlight.h"
#include "directlight.h"
#include "program.h"

using namespace com_defs;

GLuint Renderer::counter = 0;

Renderer::Renderer() :
    m_scene       (  nullptr                               ),
    m_target      (                                        ),
    m_fboId       (  0                                     ),
    m_programs    (                                        ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"             ),
    m_status      (  RendererStatus::BUFFERS_NOT_GENERATED
                   | RendererStatus::NO_SCENE              ),
    m_description (  "Empty description"                   )
{
    m_name = ++ Renderer::counter;    
}

Renderer::Renderer( Scene *scene ) :
    m_scene       ( scene                                 ),
    m_target      (                                       ),
    m_fboId       ( 0                                     ),
    m_programs    (                                       ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"            ),
    m_status      ( RendererStatus::BUFFERS_NOT_GENERATED ),
    m_description ( "Empty description"                   )
{
    m_name = ++ Renderer::counter;
}

Renderer::Renderer( const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &programs ) :
    m_scene       (  nullptr                               ),
    m_target      (                                        ),
    m_fboId       (  0                                     ),
    m_programs    (  programs                              ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"             ),
    m_status      (  RendererStatus::BUFFERS_NOT_GENERATED
                   | RendererStatus::NO_SCENE              ),
    m_description (  "Empty description"                   )
{
    m_name = ++ Renderer::counter;
}

Renderer::Renderer( const QString &description ) :
    m_scene       (  nullptr                               ),
    m_target      (                                        ),
    m_fboId       (  0                                     ),
    m_programs    (                                        ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"             ),
    m_status      (  RendererStatus::BUFFERS_NOT_GENERATED
                   | RendererStatus::NO_SCENE              ),
    m_description (  description                           )
{
    m_name = ++ Renderer::counter;
}

Renderer::Renderer( Scene *scene
                  , const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &programs ) :
    m_scene       ( scene                                 ),
    m_target      (                                       ),
    m_fboId       ( 0                                     ),
    m_programs    ( programs                              ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"            ),
    m_status      ( RendererStatus::BUFFERS_NOT_GENERATED ),
    m_description ( "Empty description"                   )
{
    m_name = ++ Renderer::counter;
}

Renderer::Renderer( Scene         *scene
                  , const QString &description ) :
    m_scene       ( scene                                 ),
    m_target      (                                       ),
    m_fboId       ( 0                                     ),
    m_programs    (                                       ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"            ),
    m_status      ( RendererStatus::BUFFERS_NOT_GENERATED ),
    m_description ( description                           )
{
    m_name = ++ Renderer::counter;
}

Renderer::Renderer( const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &programs
                  , const QString &description ) :
    m_scene       (  nullptr                               ),
    m_target      (                                        ),
    m_fboId       (  0                                     ),
    m_programs    (  programs                              ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"             ),
    m_status      (  RendererStatus::BUFFERS_NOT_GENERATED
                   | RendererStatus::NO_SCENE              ),
    m_description (  description                           )
{
    m_name = ++ Renderer::counter;
}

Renderer::Renderer( Scene         *scene
                  , const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &programs
                  , const QString &description ) :
    m_scene       ( scene                                 ),
    m_target      (                                       ),
    m_fboId       ( 0                                     ),
    m_programs    ( programs                              ),
    m_rectMesh    (  { Vertex({ 0.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  0.0f,  0.0f })
                     , Vertex({ 1.0f,  1.0f,  0.0f })
                     , Vertex({ 0.0f,  1.0f,  0.0f })
                     }
                   , { Index(0), Index(1)
                     , Index(2), Index(3)
                     }
                   , GL_QUADS
                   , "Renderer rectangle mesh"            ),
    m_status      ( RendererStatus::BUFFERS_NOT_GENERATED ),
    m_description ( description                           )
{
    m_name = ++ Renderer::counter;
}

GLuint Renderer::genBuffers() noexcept(false)
{
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
    if( (m_status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
    {
        throw RendererException(this, "Renderer exception occured");
    }

    glGenFramebuffers(1, &m_fboId);                 // Generating framebuffer object.
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboId);// Binding framebuffer object.

    GLuint *rgbaTextures[]    = { &m_target.getTexturesIds()[TargetTextures::DIFFUSE] // RGBA textures massive.
                                , &m_target.getTexturesIds()[TargetTextures::NORMALS]                                
                                , &m_target.getTexturesIds()[TargetTextures::LIGHT]
                                , &m_target.getTexturesIds()[TargetTextures::RANGE_OF_DEPTH_BLUR]
                                , &m_target.getTexturesIds()[TargetTextures::DIFFUSE_LIGHT_COMBINED]
                                , &m_target.getTexturesIds()[TargetTextures::RESULT]                                
                                };
    GLenum *rgbaAttachments[] = { &m_target.getAttachments()[TargetTextures::DIFFUSE] // RGBA textures attachments.
                                , &m_target.getAttachments()[TargetTextures::NORMALS]                                
                                , &m_target.getAttachments()[TargetTextures::LIGHT]
                                , &m_target.getAttachments()[TargetTextures::RANGE_OF_DEPTH_BLUR]
                                , &m_target.getAttachments()[TargetTextures::DIFFUSE_LIGHT_COMBINED]
                                , &m_target.getAttachments()[TargetTextures::RESULT]                                
                                };

    uint i = 0;
    for( GLuint *tex: rgbaTextures )        // Creating RGBA textures.
    {
        *rgbaAttachments[i] = GL_COLOR_ATTACHMENT0 + i;

        glGenTextures(1, tex);              // Generating RGBA texture.
        glBindTexture(GL_TEXTURE_2D, *tex); // Binding RGBA texture.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// RGBA texture parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_scene->getWidth(), m_scene->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);// Specifying 2D RGBA texture image.
        glBindTexture(GL_TEXTURE_2D, 0);    // Unbinding RGBA texture.
        glFramebufferTexture(GL_FRAMEBUFFER, *rgbaAttachments[i], *tex, 0); // Attaching RGBA texture to FBO.

        ++ i;
    }

    m_target.getAttachments()[TargetTextures::SHADOW_DIRECT] = GL_COLOR_ATTACHMENT0 + i;

    glGenTextures(1, &m_target.getTexturesIds()[TargetTextures::SHADOW_DIRECT] ); // Generating direct light shadow texture.
    glBindTexture(GL_TEXTURE_2D, m_target.getTexturesIds()[TargetTextures::SHADOW_DIRECT]); // Binding shadow texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   // Shadow texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_scene->getWidth(), m_scene->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);// Specifying 2D shadow image.
    glBindTexture(GL_TEXTURE_2D, 0);    // Unbinding shadow texture.
    glFramebufferTexture(GL_FRAMEBUFFER, m_target.getAttachments()[TargetTextures::SHADOW_DIRECT], m_target.getTexturesIds()[TargetTextures::SHADOW_DIRECT], 0);// Attaching shadow texture to FBO.

    ++ i;

    m_target.getAttachments()[TargetTextures::DEPTH] = GL_DEPTH_ATTACHMENT;

    glGenTextures(1, &m_target.getTexturesIds()[TargetTextures::DEPTH] );// Generating depth texture.
    glBindTexture(GL_TEXTURE_2D, m_target.getTexturesIds()[TargetTextures::DEPTH] );// Binding depth texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   // Depth texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, m_scene->getWidth(), m_scene->getHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);// Specifying 2D depth texture image.
    glBindTexture(GL_TEXTURE_2D, 0);        // Unbinding depth texture.
    glFramebufferTexture(GL_FRAMEBUFFER, m_target.getAttachments()[TargetTextures::DEPTH], m_target.getTexturesIds()[TargetTextures::DEPTH], 0);// Attaching depth texture to FBO.


    m_status &= ~RendererStatus::BUFFERS_NOT_GENERATED;// Disabling RendererStatus::BUFFERS_NOT_GENERATED flag.


    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);// Checking FBO for errors.
    ( fboStatus != GL_FRAMEBUFFER_COMPLETE ) ? m_status |=  RendererStatus::FBO_NOT_COMPLETED
                                             : m_status &= ~RendererStatus::FBO_NOT_COMPLETED;

    if( (m_status & RendererStatus::FBO_NOT_COMPLETED) == RendererStatus::FBO_NOT_COMPLETED )
    {
        throw RendererException(this, "Renderer exception occured", fboStatus);
    }


    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Unbinding framebuffer object.


    m_rectMesh.genBuffers();    // Generating rectangle VBO & IBO buffers.
    m_rectMesh.pushData();      // Pushing data to generated rectangle VBO & IBO buffers.


    return m_fboId;
}

GLuint Renderer::deleteBuffers()
{
    GLuint *textures[]    = { &m_target.getTexturesIds()[TargetTextures::DIFFUSE]  // Textures to delete.
                            , &m_target.getTexturesIds()[TargetTextures::NORMALS]                            
                            , &m_target.getTexturesIds()[TargetTextures::DEPTH]                           
                            , &m_target.getTexturesIds()[TargetTextures::LIGHT]
                            , &m_target.getTexturesIds()[TargetTextures::RANGE_OF_DEPTH_BLUR]
                            , &m_target.getTexturesIds()[TargetTextures::DIFFUSE_LIGHT_COMBINED]
                            , &m_target.getTexturesIds()[TargetTextures::RESULT]
                            , &m_target.getTexturesIds()[TargetTextures::SHADOW_DIRECT]
                            };

    GLenum *attachments[] = { &m_target.getAttachments()[TargetTextures::DIFFUSE]  // Attachments to clear.
                            , &m_target.getAttachments()[TargetTextures::NORMALS]
                            , &m_target.getAttachments()[TargetTextures::DEPTH]                           
                            , &m_target.getAttachments()[TargetTextures::LIGHT]
                            , &m_target.getAttachments()[TargetTextures::RANGE_OF_DEPTH_BLUR]
                            , &m_target.getAttachments()[TargetTextures::DIFFUSE_LIGHT_COMBINED]
                            , &m_target.getAttachments()[TargetTextures::RESULT]
                            , &m_target.getAttachments()[TargetTextures::SHADOW_DIRECT]
                            };

    GLuint texValues[NUM_OF_RENDERER_TEXTURES]; // Values of textures ids.

    uint i = 0;
    for( GLuint *tex : textures )
    {
        texValues[i] = *tex;
        *tex = 0;                 // Setting textures ids to 0.
        *attachments[i] = 0;      // Setting attachments to 0.

        ++ i;
    }

    glDeleteTextures(NUM_OF_RENDERER_TEXTURES, &(texValues[0]) );// Deleting textures from OpenGL.

    GLuint deletedFBOId = m_fboId;
    glDeleteFramebuffers(1, &m_fboId);

    m_fboId = 0;


    m_rectMesh.deleteBuffers(); // Deleting VBO & IBO rectangle mesh buffers.


    m_status |= RendererStatus::BUFFERS_NOT_GENERATED;

    return deletedFBOId;
}

void Renderer::renderGBuffer() noexcept(false)
{
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
    if( (m_status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
    {
        throw RendererException(this, "Renderer exception occured");
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboId); // Binding framebuffer for rendering.
    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);// Checking FBO for errors.
    ( fboStatus != GL_FRAMEBUFFER_COMPLETE ) ? m_status |=  RendererStatus::FBO_NOT_COMPLETED
                                             : m_status &= ~RendererStatus::FBO_NOT_COMPLETED;

    if( m_status != RendererStatus::FINE )
    {
        //std::cerr << "Error. " << fboStatus << std::endl;
        throw RendererException(this, "Renderer exception occured", fboStatus);
    }

    QVector<GLenum> rgbaAttachments { m_target.getAttachments()[TargetTextures::DIFFUSE]  // RGBA attachments to render in.
                                    , m_target.getAttachments()[TargetTextures::NORMALS]                                   
                                    };
    glDrawBuffers(rgbaAttachments.length(), rgbaAttachments.constData() );// Specifying color buffers to draw into.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(m_scene->getX(), m_scene->getY(), m_scene->getWidth(), m_scene->getHeight() );


    for( std::weak_ptr<Shape> weakShape : m_scene->getShapes() )
    {
        std::shared_ptr<Shape> shape = weakShape.lock();
        if( shape )
        {
            shape->draw(&m_scene->getCamera() ); // Drawing shapes to geometry buffer.
        }
    }


    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Unbinding framebuffer.
}

void Renderer::renderLBuffer() noexcept(false)
{
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
    if( (m_status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
    {
        throw RendererException(this, "Renderer exception occured");
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboId); // Binding framebuffer for rendering.
    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);// Checking FBO for errors.
    ( fboStatus != GL_FRAMEBUFFER_COMPLETE ) ? m_status |=  RendererStatus::FBO_NOT_COMPLETED
                                             : m_status &= ~RendererStatus::FBO_NOT_COMPLETED;
    if( m_status != RendererStatus::FINE )
    {
        throw RendererException(this, "Renderer exception occured", fboStatus);
    }

    QVector<GLenum> rgbaAttachments { m_target.getAttachments()[TargetTextures::LIGHT]  // RGBA attachments to render in.
                                    , m_target.getAttachments()[TargetTextures::SHADOW_DIRECT]
                                    };

    glDrawBuffers(rgbaAttachments.length(), rgbaAttachments.constData() );// Specifying color buffers to draw into.

    glClear(GL_COLOR_BUFFER_BIT);   // Clearing color buffer.
    glDepthMask(GL_FALSE);          // Disabling writing to depth buffer.    
    glDisable(GL_CULL_FACE);        // Disabling cull face.    
    glEnable(GL_BLEND);             // Disabling blending.
    glBlendFunc(GL_ONE, GL_ZERO);   // Setting blending pixel arithmetic.

    glViewport(m_scene->getX(), m_scene->getY(), m_scene->getWidth(), m_scene->getHeight() );

    QVector4D  clearColor;
    glGetFloatv(GL_COLOR_CLEAR_VALUE, &(clearColor[0]) ); // Getting current clear color.

    uint counter = 0;
    for( std::weak_ptr<Light> weakLight : m_scene->getLights() )
    {
        std::shared_ptr<Light> light = weakLight.lock();
        if( light )
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    // Setting white clear color.
            //glClear(GL_COLOR_BUFFER_BIT);
            light->draw(this);  // Drawing lights to light buffer.
            if( counter == 0 ) {
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// Setting black clear color.
                glBlendFunc(GL_ONE, GL_ONE);        // Setting blending pixel arithmetic.
            }
            counter ++;
        }
    }


    glEnable(GL_CULL_FACE);     // Enabling cull face.
    glBlendFunc(GL_ONE, GL_ZERO);// Setting blending pixel arithmetic.
    glDisable(GL_BLEND);        // Disabling blending.    
    glDepthMask(GL_TRUE);       // Enabling writing to depth buffer.
    glClearColor(clearColor.x(), clearColor.y(), clearColor.z(), clearColor.w() );// Setting previous clear color.


    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Unbinding framebuffer.
}

void Renderer::postProcess() noexcept(false)
{
    combineLight( m_target.getTexturesIds()[TargetTextures::DIFFUSE], Uniform::DIFFUSE_TEXTURE_2D
                , m_target.getTexturesIds()[TargetTextures::LIGHT],   Uniform::LIGHT_TEXTURE_2D
                , m_target.getAttachments()[TargetTextures::DIFFUSE_LIGHT_COMBINED]
                , m_programs.value(RendererPrograms::LIGHT_COMBINER) );
    writeBlurRange( m_target.getTexturesIds()[TargetTextures::DEPTH], Uniform::DEPTH_TEXTURE_2D
                  , m_target.getTexturesIds()[TargetTextures::DIFFUSE_LIGHT_COMBINED], Uniform::DIFFUSE_LIGHT_COMBINED_2D
                  , m_target.getAttachments()[TargetTextures::RANGE_OF_DEPTH_BLUR]
                  , FOCAL_DISTANCE
                  , FOCAL_RANGE
                  , m_programs.value(RendererPrograms::BLUR_RANGER) );
}

void Renderer::finalRender() noexcept(false)
{
    drawTexture2D( m_target.getTexturesIds()[TargetTextures::DIFFUSE_LIGHT_COMBINED]   // Drawing 2D texture.
                 , Uniform::SOME_TEXTURE_2D
                 , m_programs.value(RendererPrograms::TEXTURE_2D_RENDERER) );
}

const Renderer & Renderer::operator = (const Renderer &renderer)
{
    m_scene       = renderer.m_scene;
    m_programs    = renderer.m_programs;
    m_description = renderer.m_description;

    return *this;
}

bool Renderer::operator == (const Renderer &renderer) const
{
    bool equal = false;

    QList<std::shared_ptr<const Program> > thesePrograms, otherPrograms;
    for(  QHash<RendererPrograms::Programs, std::weak_ptr<Program> >::const_iterator it = m_programs.constBegin()
        ; it != m_programs.constEnd()
        ; ++it )
    {
        thesePrograms << it.value().lock();
    }
    for(  QHash<RendererPrograms::Programs, std::weak_ptr<Program> >::const_iterator it = renderer.m_programs.constBegin()
        ; it != renderer.m_programs.constEnd()
        ; ++it )
    {
        otherPrograms << it.value().lock();
    }

    bool programsEqual = false;
    if( thesePrograms.length() == otherPrograms.length() )
    {
        programsEqual = true;
        for( int i = 0; i < thesePrograms.length(); ++i )
        {
            if( thesePrograms[i].get() != otherPrograms[i].get() )
            {
                programsEqual = false;
                break;
            }
        }        
    }

    if(   m_scene       == renderer.m_scene
      &&  programsEqual )
    {
        equal = true;
    }

    return equal;
}

bool Renderer::operator != (const Renderer &renderer) const
{
    return !(*this == renderer);
}

void Renderer::setScene(Scene *scene)
{
    m_scene = scene;
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
}

const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &Renderer::getPrograms() const
{
    return m_programs;
}

QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &Renderer::getPrograms()
{
    return m_programs;
}

void Renderer::setPrograms(const QHash<RendererPrograms::Programs, std::weak_ptr<Program> > &programs)
{
    m_programs = programs;
}

void Renderer::setDescription(const QString &description)
{
    m_description = description;
}

void Renderer::drawTexture2D(GLuint textureId, const char *textureUniform, std::weak_ptr<Program> weakProgram) noexcept(false)
{
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
    if( (m_status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
    {
        throw RendererException(this, "Renderer exception occured");
    }

    static GLuint attempts = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport(m_scene->getX(), m_scene->getY(), m_scene->getWidth(), m_scene->getHeight() );

    GLboolean vboIsFine = glIsBuffer(m_rectMesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(m_rectMesh.getIBOId() );
    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? m_status |=  RendererStatus::INVALID_RECTANGLE_BUFFERS
                                                       : m_status &= ~RendererStatus::INVALID_RECTANGLE_BUFFERS;
    if( (m_status & RendererStatus::INVALID_RECTANGLE_BUFFERS) == RendererStatus::INVALID_RECTANGLE_BUFFERS ) // Checking rectangle buffers.
    {
        ++ attempts;
        m_rectMesh.deleteBuffers();                     // Refilling VBO & IBO rectangle data.
        m_rectMesh.genBuffers();
        m_rectMesh.fill();
        m_rectMesh.pushData();
        drawTexture2D(textureId, textureUniform, weakProgram); // Trying to draw rectangle NUM_OF_RENDERER_RECT_DRAW_ATTEMPTS times.
        if( attempts > NUM_OF_RENDERER_RECT_DRAW_ATTEMPTS ) // Attempts limit depleted.
        {
            attempts = 0;
            throw RendererException(this, "Renderer exception occured");
        }
        return;
    }
    else
    {
        attempts = 0;
    }

    std::shared_ptr<Program> program = weakProgram.lock();
    ( !program ) ? m_status |=  RendererStatus::NO_RENDERER_PROGRAM
                 : m_status &= ~RendererStatus::NO_RENDERER_PROGRAM;

    if( (m_status & RendererStatus::NO_RENDERER_PROGRAM) == RendererStatus::NO_RENDERER_PROGRAM ) // Checking if renderer program is set.
    {
        throw RendererException(this, "Renderer exception occured");
    }

    program->use();                 // Using rendering shading program.

    glBindBuffer(GL_ARRAY_BUFFER, m_rectMesh.getVBOId() );// Binding rectangle VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);

    GLsizei coordinatesShift  =   0;

    glEnableVertexAttribArray(Attribute::COORDINATE);   // Enabling coordinate attribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rectMesh.getIBOId() ); // Binding rectangle IBO buffer.

    GLint texture2DLocation = glGetUniformLocation( program->getId()   // Getting 2D texture uniform location.
                                                  , textureUniform
                                                  );
    glUniform1i(texture2DLocation, 0);

    glActiveTexture(GL_TEXTURE0);       // Activating texture.
    glBindTexture(GL_TEXTURE_2D, textureId); // Binding texture.


    glDrawElements(m_rectMesh.getMode(), m_rectMesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) ); // Drawing textured rectangle.


    glDisableVertexAttribArray(Attribute::COORDINATE);      // Disabling coordinate attribute.

    glBindTexture(GL_TEXTURE_2D, 0);             // Unbinding texture.
    glBindBuffer(GL_ARRAY_BUFFER, 0);            // Unbinding rectangle VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);    // Unbinding rectangle IBO buffer.


    program->stopUse();             // Stop using rendering shading program.
}

void Renderer::combineLight( GLuint diffuseTexId, const char *diffuseUniform
                           , GLuint lightTexId,   const char *lightUniform
                           , GLenum resultTextureAttachment
                           , std::weak_ptr<Program>           weakProgram ) noexcept(false)
{
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
    if( (m_status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
    {
        throw RendererException(this, "Renderer exception occured");
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboId); // Binding framebuffer for rendering.
    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);// Checking FBO for errors.
    ( fboStatus != GL_FRAMEBUFFER_COMPLETE ) ? m_status |=  RendererStatus::FBO_NOT_COMPLETED
                                             : m_status &= ~RendererStatus::FBO_NOT_COMPLETED;
    if( m_status != RendererStatus::FINE )
    {
        throw RendererException(this, "Renderer exception occured", fboStatus);
    }

    QVector<GLenum> rgbaAttachments { resultTextureAttachment }; // RGBA attachments to render in.
    glDrawBuffers(rgbaAttachments.length(), rgbaAttachments.constData() ); // Specifying color buffers to draw into.

    glDepthMask(GL_FALSE);          // Disabling writing to depth buffer.
    glViewport(m_scene->getX(), m_scene->getY(), m_scene->getWidth(), m_scene->getHeight() );

    static GLuint attempts = 0;

    GLboolean vboIsFine = glIsBuffer(m_rectMesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(m_rectMesh.getIBOId() );
    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? m_status |=  RendererStatus::INVALID_RECTANGLE_BUFFERS
                                                       : m_status &= ~RendererStatus::INVALID_RECTANGLE_BUFFERS;
    if( (m_status & RendererStatus::INVALID_RECTANGLE_BUFFERS) == RendererStatus::INVALID_RECTANGLE_BUFFERS ) // Checking rectangle buffers.
    {
        ++ attempts;
        m_rectMesh.deleteBuffers();                 // Refilling VBO & IBO rectangle data.
        m_rectMesh.genBuffers();
        m_rectMesh.fill();
        m_rectMesh.pushData();
        combineLight(diffuseTexId, diffuseUniform, lightTexId, lightUniform, resultTextureAttachment, weakProgram); // Trying to combine light NUM_OF_RENDERER_LIGHT_COMBINE_ATTEMPTS times.
        if( attempts > NUM_OF_RENDERER_LIGHT_COMBINE_ATTEMPTS ) // Attempts limit depleted.
        {
            attempts = 0;
            throw RendererException(this, "Renderer exception occured");
        }
        return;
    }
    else
    {
        attempts = 0;
    }

    std::shared_ptr<Program> program = weakProgram.lock();
    ( !program ) ? m_status |=  RendererStatus::NO_RENDERER_PROGRAM
                 : m_status &= ~RendererStatus::NO_RENDERER_PROGRAM;
    if( (m_status & RendererStatus::NO_RENDERER_PROGRAM) == RendererStatus::NO_RENDERER_PROGRAM ) // Checking if renderer program is set.
    {
        throw RendererException(this, "Renderer exception occured");
    }

    program->use();                 // Using rendering shading program.

    glBindBuffer(GL_ARRAY_BUFFER, m_rectMesh.getVBOId() );// Binding rectangle VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);

    GLsizei coordinatesShift  =   0;

    glEnableVertexAttribArray(Attribute::COORDINATE);   // Enabling coordinate attribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rectMesh.getIBOId() ); // Binding rectangle IBO buffer.
    GLint diffuseTextureLocation = glGetUniformLocation( program->getId() // Getting 2D diffuse texture uniform location.
                                                       , diffuseUniform
                                                       );
    GLint lightTextureLocation   = glGetUniformLocation( program->getId() // Getting 2D light texture uniform location.
                                                       , lightUniform
                                                       );
    GLint  texturesLocations[] { diffuseTextureLocation
                               , lightTextureLocation };
    GLuint texturesIds[] { diffuseTexId
                         , lightTexId };
    uint length = 0;
    uint i = 0;
    for( GLint textureLocation : texturesLocations )
    {
        glUniform1i(textureLocation, i);
        glActiveTexture(GL_TEXTURE0 + i);   // Activating texture.
        glBindTexture(GL_TEXTURE_2D, texturesIds[i]); // Binding texture.

        ++ i;
    }
    length = i;


    glDrawElements(m_rectMesh.getMode(), m_rectMesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) ); // Drawing rectangle.


    glDisableVertexAttribArray(Attribute::COORDINATE);  // Disabling coordinate attribute.

    for( uint j = 0; j < length; ++j )
    {
        glActiveTexture(GL_TEXTURE0 + j);         // Activating texture.
        glBindTexture(GL_TEXTURE_2D, 0);          // Unbinding texture.
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);             // Unbinding VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);     // Unbinding IBO buffer.


    program->stopUse();

    glDepthMask(GL_TRUE);          // Enabling writing to depth buffer.
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Unbinding framebuffer.
}

void Renderer::writeBlurRange( GLuint  depthTextureId,        const char *depthUniform
                             , GLuint  diffuseLightTextureId, const char *diffuseLightUniform
                             , GLenum  resultTextureAttachment
                             , GLfloat focalDistance
                             , GLfloat focalRange
                             , std::weak_ptr<Program> weakProgram ) noexcept(false)
{
    ( !m_scene ) ? m_status |=  RendererStatus::NO_SCENE
                 : m_status &= ~RendererStatus::NO_SCENE;
    if( (m_status & RendererStatus::NO_SCENE) == RendererStatus::NO_SCENE )
    {
        throw RendererException(this, "Renderer exception occured");
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboId); // Binding framebuffer for rendering.
    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);// Checking FBO for errors.
    ( fboStatus != GL_FRAMEBUFFER_COMPLETE ) ? m_status |=  RendererStatus::FBO_NOT_COMPLETED
                                             : m_status &= ~RendererStatus::FBO_NOT_COMPLETED;
    if( m_status != RendererStatus::FINE )
    {
        throw RendererException(this, "Renderer exception occured", fboStatus);
    }

    QVector<GLenum> rgbaAttachments { resultTextureAttachment }; // RGBA attachments to render in.
    glDrawBuffers(rgbaAttachments.length(), rgbaAttachments.constData() ); // Specifying color buffers to draw into.

    glDepthMask(GL_FALSE);          // Disabling writing to depth buffer.
    glViewport(m_scene->getX(), m_scene->getY(), m_scene->getWidth(), m_scene->getHeight() );

    static GLuint attempts= 0;

    GLboolean vboIsFine = glIsBuffer(m_rectMesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(m_rectMesh.getIBOId() );

    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? m_status |=  RendererStatus::INVALID_RECTANGLE_BUFFERS
                                                       : m_status &= ~RendererStatus::INVALID_RECTANGLE_BUFFERS;
    if( (m_status & RendererStatus::INVALID_RECTANGLE_BUFFERS) == RendererStatus::INVALID_RECTANGLE_BUFFERS ) // Checking rectangle buffers.
    {
        ++ attempts;
        m_rectMesh.deleteBuffers();                 // Refilling VBO & IBO rectangle data.
        m_rectMesh.genBuffers();
        m_rectMesh.fill();
        m_rectMesh.pushData();
        writeBlurRange( depthTextureId,          depthUniform
                      , diffuseLightTextureId,   diffuseLightUniform
                      , resultTextureAttachment
                      , focalDistance
                      , focalRange
                      , weakProgram );
        if( attempts > NUM_OF_RENDERER_WRITING_BLUR_RANGE_ATTEMPTS ) // Attempts limit depleted.
        {
            attempts = 0;
            throw RendererException(this, "Renderer exception occured");
        }
        return;
    }
    else
    {
        attempts = 0;
    }

    std::shared_ptr<Program> program = weakProgram.lock();
    ( !program ) ? m_status |=  RendererStatus::NO_RENDERER_PROGRAM
                            :  ~RendererStatus::NO_RENDERER_PROGRAM;
    if( (m_status & RendererStatus::NO_RENDERER_PROGRAM) == RendererStatus::NO_RENDERER_PROGRAM ) // Checking if renderer program is set.
    {
        throw RendererException(this, "Renderer exception occured");
    }

    program->use();                 // Using rendering shading program.

    glBindBuffer(GL_ARRAY_BUFFER, m_rectMesh.getVBOId() );// Binding rectangle VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);
    GLsizei coordinatesShift  =   0;

    glEnableVertexAttribArray(Attribute::COORDINATE);   // Enabling coordinate stribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rectMesh.getIBOId() ); // Binding rectangle IBO buffer.
    GLint depthTextureLocation        = glGetUniformLocation( program->getId() // Getting 2D depth texture uniform location.
                                                            , depthUniform
                                                            );
    GLint diffuseLightTextureLocation = glGetUniformLocation( program->getId() // Getting 2D diffuse light texture uniform location.
                                                            , diffuseLightUniform
                                                            );
    GLint invProjectionLocation       = glGetUniformLocation( program->getId() // Getting inverse projection matrix uniform location.
                                                            , Uniform::INV_PROJECTION
                                                            );
    GLint focalDistanceLocation       = glGetUniformLocation( program->getId() // Getting focal distance uniform location.
                                                            , Uniform::FOCAL_DISTANCE
                                                            );
    GLint focalRangeLocation          = glGetUniformLocation( program->getId() // Getting focal range uniform location.
                                                            , Uniform::FOCAL_RANGE
                                                            );

    QMatrix4x4 projection    = m_scene->getCamera().getProjection();        // Getting projection matrix.
    QMatrix4x4 invProjection = projection.inverted();                       // Inversing projection matrix.

    glUniformMatrix4fv(invProjectionLocation,        1, GL_FALSE,  invProjection.constData()    ); // Specifying the value of an inverse projection uniform.
    glUniform1f(focalDistanceLocation,                             focalDistance                ); // Specifying the value of focal distance uniform.
    glUniform1f(focalRangeLocation,                                focalRange                   ); // Specifying the value of focal range uniform.

    GLint  texturesLocations[] { depthTextureLocation
                               , diffuseLightTextureLocation };
    GLuint texturesIds[] { depthTextureId
                         , diffuseLightTextureId };
    uint length = 0;
    uint i = 0;
    for( GLint textureLocation : texturesLocations )
    {
        glUniform1i(textureLocation, i);
        glActiveTexture(GL_TEXTURE0 + i);    // Activating texture.
        glBindTexture(GL_TEXTURE_2D, texturesIds[i]); // Binding texture.

        ++i;
    }
    length = i;


    glDrawElements(m_rectMesh.getMode(), m_rectMesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) ); // Drawing rectange.


    glDisableVertexAttribArray(Attribute::COORDINATE);  // Disabling coordinate attribute.

    for( uint j = 0; j < length; ++j )
    {
        glActiveTexture(GL_TEXTURE0 + j);         // Activating texture.
        glBindTexture(GL_TEXTURE_2D, 0);          // Unbinding texture.
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);             // Unbinding VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);     // Unbinding IBO buffer.


    program->stopUse();

    glDepthMask(GL_TRUE);          // Enabling writing to depth buffer.
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Unbinding framebuffer.
}

Renderer::Renderer( const Renderer &renderer ) :
    m_scene       ( renderer.m_scene       ),
    m_target      ( renderer.m_target      ),
    m_name        ( renderer.m_name        ),
    m_fboId       ( renderer.m_fboId       ),
    m_programs    ( renderer.m_programs    ),
    m_rectMesh    ( renderer.m_rectMesh    ),
    m_status      ( renderer.m_status      ),
    m_description ( renderer.m_description )
{
}
