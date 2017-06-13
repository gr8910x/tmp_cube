#include "directlight.h"
#include "scene.h"
#include "camera.h"
#include "shape.h"
#include "mesh.h"
#include "renderer.h"
#include "program.h"
#include "lightexception.h"

using namespace com_defs;

GLuint DirectLight::counter = 0;

DirectLight::DirectLight() :
    Light          (                     ),
    m_direction    ( 0.0f,  0.0f,  -1.0f ),
    m_program      (                     ),
    m_shadowCamera(                      )
{
    ++ DirectLight::counter;
}

DirectLight::DirectLight(const QVector3D &direction) :
    Light         (           ),
    m_direction   ( direction ),
    m_program     (           ),
    m_shadowCamera(           )
{
    ++ DirectLight::counter;
}

DirectLight::DirectLight(const QVector4D         &lightColor
                        , GLfloat                 intensity
                        , const QVector3D        &direction
                        , std::weak_ptr<Program>  program
                        , const QString          &description
                        ) :
    Light          ( lightColor, intensity, description ),
    m_direction    ( direction                          ),
    m_program      ( program                            ),
    m_shadowCamera (                                    )
{
    ++ DirectLight::counter;
}

LightType DirectLight::getType() const
{
    return LightType::DIRECT;
}

void DirectLight::draw(Renderer *renderer) noexcept(false)
{
    drawShadow(renderer); // Drawing shadow map.
    drawLight(renderer);  // Drawing into light buffer.
}

const DirectLight & DirectLight::operator = ( const DirectLight &light )
{
    Light::operator = (light);
    m_direction     = light.m_direction;
    m_program       = light.m_program;
    m_shadowCamera  = light.m_shadowCamera;

    return *this;
}

bool  DirectLight::operator == (const DirectLight &light) const
{
    std::shared_ptr<Program> thisProgram    = m_program.lock();
    std::shared_ptr<Program> anotherProgram = light.m_program.lock();

    bool equal = false;

    if(  Light::operator   == (light)
      && m_direction       == light.m_direction
      && thisProgram.get() == anotherProgram.get()
      )
    {
        equal = true;
    }

    return equal;
}

bool  DirectLight::operator != (const DirectLight &light) const
{
    return !(*this == light);
}

void DirectLight::setDirection(const QVector3D &direction)
{
    m_direction = direction;
}

void DirectLight::setDirection(GLfloat x, GLfloat y, GLfloat z)
{
    m_direction.setX(x);
    m_direction.setY(y);
    m_direction.setZ(z);
}

void DirectLight::setProgram(std::weak_ptr<Program> program)
{
    m_program = program;
}

std::shared_ptr<DirectLight> DirectLight::createObject()
{
    return std::make_shared<DirectLight>();
}

DirectLight::DirectLight( const DirectLight &light ) :
    Light         ( light                ),
    m_direction   ( light.m_direction    ),
    m_program     ( light.m_program      ),
    m_shadowCamera( light.m_shadowCamera )
{
}

void DirectLight::setShadowCamera(const Camera &shadowCamera)
{
    m_shadowCamera = shadowCamera;
}

void DirectLight::drawLight(Renderer *renderer) noexcept(false)
{
    Mesh &mesh = renderer->getRectMesh();

    static GLuint attempts = 0;

    GLboolean vboIsFine = glIsBuffer(mesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(mesh.getIBOId() );
    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? getStatus() |=  LightStatus::INVALID_BUFFERS
                                                       : getStatus() &= ~LightStatus::INVALID_BUFFERS;
    if( (getStatus() & LightStatus::INVALID_BUFFERS) == LightStatus::INVALID_BUFFERS ) // Checking light buffers.
    {
        ++ attempts;
        mesh.deleteBuffers();                           // Refilling VBO and IBO data.
        mesh.genBuffers();
        mesh.fill();
        mesh.pushData();
        draw(renderer);                                 // Trying to draw light NUM_OF_LIGHT_DRAW_ATTEMPTS times.
        if( attempts > NUM_OF_LIGHT_DRAW_ATTEMPTS )
        {
            attempts = 0;
            throw LightException(this, "Direct light exception occured");
        }
        return;
    }
    else
    {
        attempts = 0;
    }


    std::shared_ptr<Program> program = m_program.lock();
    ( !program ) ? getStatus() |=  LightStatus::NO_PROGRAM
                 : getStatus() &= ~LightStatus::NO_PROGRAM;
    if( (getStatus() & LightStatus::NO_PROGRAM) == LightStatus::NO_PROGRAM ) // Checking if program is set.
    {
        throw LightException(this, "Direct light exception occured");
    }

    program->use();     // Using shading program.


    glBindBuffer(GL_ARRAY_BUFFER, mesh.getVBOId() );  // Binding VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);
    GLsizei coordinatesShift  =   0;                  //

    glEnableVertexAttribArray(Attribute::COORDINATE); // Enabling coordinate attribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBOId() );  // Binding IBO buffer.

    GLint invProjectionViewLocation    = glGetUniformLocation( program->getId()   // Getting inverse projection view matrix uniform location.
                                                             , Uniform::INV_PROJECTION_VIEW
                                                             );
    GLint lightColorLocation           = glGetUniformLocation( program->getId()   // Getting light color uniform location.
                                                             , Uniform::LIGHT_COLOR
                                                             );
    GLint lightDirectionLocation       = glGetUniformLocation( program->getId()   // Getting light direction uniform location.
                                                             , Uniform::LIGHT_DIRECTION
                                                             );
    GLint normalsTexture2DLocation     = glGetUniformLocation( program->getId()   // Getting normals 2D texture uniform location.
                                                             , Uniform::NORMALS_TEXTURE_2D
                                                             );
    GLint depthTexture2DLocation       = glGetUniformLocation( program->getId()   // Getting depth 2D texture uniform location.
                                                             , Uniform::DEPTH_TEXTURE_2D
                                                             );
    GLint shadowProjectionViewLocation = glGetUniformLocation( program->getId()   // Getting shadow projection view matrix uniform location.
                                                             , Uniform::SHADOW_PROJECTION_VIEW
                                                             );
    GLint shadowTexture2DLocation      = glGetUniformLocation( program->getId()   // Gtting shadow 2D texture uniform location.
                                                             , Uniform::SHADOW_TEXTURE_2D
                                                             );

    QMatrix4x4 projectionView       = renderer->getScene()->getCamera().getProjectionView();    // Getting projection view matrix.
    QMatrix4x4 invProjectionView    = projectionView.inverted();                                // Inversing projection view matrix.
    QMatrix4x4 shadowProjectionView = m_shadowCamera.getProjectionView();                       // Getting shadow projection view matrix.

    glUniformMatrix4fv(invProjectionViewLocation,    1, GL_FALSE,  invProjectionView.constData()    );// Specifying the value of an inverse projection view uniform.
    glUniform4fv(lightColorLocation,                 1,           &(getLightColor()[0])             );// Specifying the value of light color uniform.
    glUniform3fv(lightDirectionLocation,             1,           &(m_direction[0])                 );// Specifying the value of light direction uniform.
    glUniformMatrix4fv(shadowProjectionViewLocation, 1, GL_FALSE,  shadowProjectionView.constData() );// Specifying the value of shadow projection view uniform.

    GLint  texturesLocations[] { normalsTexture2DLocation
                               , depthTexture2DLocation
                               , shadowTexture2DLocation };
    GLuint texturesIds[] { renderer->getRenderTarget().getTexturesIds().value(TargetTextures::NORMALS)
                         , renderer->getRenderTarget().getTexturesIds().value(TargetTextures::DEPTH)
                         , renderer->getRenderTarget().getTexturesIds().value(TargetTextures::SHADOW_DIRECT) };
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


    glDrawElements(mesh.getMode(), mesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) );   // Drawing elements.


    glDisableVertexAttribArray(Attribute::COORDINATE);  // Disabling coordinate attribute.

    for( uint j = 0; j < length; ++j )
    {
        glActiveTexture(GL_TEXTURE0 + j);   // Activating texture.
        glBindTexture(GL_TEXTURE_2D, 0);    // Unbinding texture.
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);           // Unbinding VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   // Unbinding IBO buffer.


    program->stopUse();
}

void DirectLight::drawShadow(Renderer *renderer) noexcept(false)
{
    Camera &camera = renderer->getScene()->getCamera();
    m_shadowCamera.setZNear(camera.getZNear() );
    m_shadowCamera.setZFar(camera.getZFar() );
    m_shadowCamera.setFovy(camera.getFovy() );

    QVector3D direction = m_direction;
    aux_funcs::normalize(direction);
    QVector3D gazePoint = camera.getGazePoint();
    QVector3D centerOfBox { 0.0f
                          , 0.0f
                          , ( camera.getZFar() - camera.getZNear() ) / 2.0f
                          };
    QVector3D position = (gazePoint - direction * centerOfBox.z() );

    m_shadowCamera.setGazePoint(gazePoint);
    m_shadowCamera.setPosition(position);

    glDisable(GL_BLEND);
    QList<std::weak_ptr<Shape> > &shapes = renderer->getScene()->getShapes();
    for( std::weak_ptr<Shape> weakShape : shapes )
    {
        std::shared_ptr<Shape> shape = weakShape.lock();
        shape->drawShadow(&m_shadowCamera);
    }
    glEnable(GL_BLEND);

}
