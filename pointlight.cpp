#include "pointlight.h"
#include "camera.h"
#include "renderer.h"
#include "scene.h"
#include "program.h"
#include "lightexception.h"

using namespace com_defs;

GLuint PointLight::counter = 0;

PointLight::PointLight() :
    Light        (        ),
    m_mesh       (        ),
    m_transforms (        ),
    m_radius     ( 1.0f   ),
    m_program    (        ),   
    m_position   (        )
{
    ++ PointLight::counter;
}

PointLight::PointLight( const Mesh       &mesh
                      , const Transforms &transforms
                      , GLfloat           radius
                      , const QVector3D  &position ) :
    Light        (            ),
    m_mesh       ( mesh       ),
    m_transforms ( transforms ),
    m_radius     ( radius     ),
    m_program    (            ),   
    m_position   ( position   )
{
    ++ PointLight::counter;
}

PointLight::PointLight( const QVector4D         &lightColor
                      , GLfloat                 intensity
                      , const Mesh             &mesh
                      , const Transforms       &transforms
                      , GLfloat                 radius
                      , const QVector3D        &position
                      , std::weak_ptr<Program>  program
                      , const QString          &description
                      ) :
    Light        ( lightColor, intensity, description ),
    m_mesh       ( mesh                               ),
    m_transforms ( transforms                         ),
    m_radius     ( radius                             ),
    m_program    ( program                            ),   
    m_position   ( position                           )
{
    ++ PointLight::counter;
}

PointLight::~PointLight()
{
    m_mesh.deleteBuffers();
}

LightType PointLight::getType() const
{
    return LightType::POINT;
}

void PointLight::draw(Renderer *renderer) noexcept(false)
{
    static GLuint attempts = 0;

    GLboolean vboIsFine = glIsBuffer(m_mesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(m_mesh.getIBOId() );
    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? getStatus() |=  LightStatus::INVALID_BUFFERS
                                                       : getStatus() &= ~LightStatus::INVALID_BUFFERS;
    if( (getStatus() & LightStatus::INVALID_BUFFERS) == LightStatus::INVALID_BUFFERS ) // Checking light buffers.
    {
        ++ attempts;
        m_mesh.deleteBuffers();                         // Refilling VBO and IBO data.
        m_mesh.genBuffers();
        m_mesh.fill();
        m_mesh.pushData();
        draw(renderer);                                 // Trying to draw light NUM_OF_LIGHT_DRAW_ATTEMPTS times.
        if( attempts > NUM_OF_LIGHT_DRAW_ATTEMPTS )     // Attempts limit depleted.
        {
            attempts = 0;
            throw LightException(this, "Point light exception occured");
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
        throw LightException(this, "Point light exception occured");
    }


    program->use();     // Using shading program.


    glBindBuffer(GL_ARRAY_BUFFER, m_mesh.getVBOId() );// Binding VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);
    GLsizei coordinatesShift  =   0;

    glEnableVertexAttribArray(Attribute::COORDINATE); // Enabling coordinate attribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBOId() );// Binding IBO buffer.

    GLint projectionViewLocation    = glGetUniformLocation( program->getId()   // Getting projection view matrix uniform location.
                                                          , Uniform::PROJECTION_VIEW
                                                          );
    GLint modelLocation             = glGetUniformLocation( program->getId()   // Getting model matrix uniform location.
                                                          , Uniform::MODEL
                                                          );
    GLint invProjectionViewLocation = glGetUniformLocation( program->getId()   // Getting inverse projection view matrix uniform location.
                                                          , Uniform::INV_PROJECTION_VIEW
                                                          );
    GLint lightColorLocation        = glGetUniformLocation( program->getId()   // Getting light color uniform location.
                                                          , Uniform::LIGHT_COLOR
                                                          );
    GLint lightPositionLocation     = glGetUniformLocation( program->getId()   // Getting light position uniform location.
                                                          , Uniform::LIGHT_POSITION
                                                          );
    GLint lightRadiusLocation       = glGetUniformLocation( program->getId()   // Getting light radius uniform location.
                                                          , Uniform::LIGHT_RADIUS
                                                          );    
    GLint normalsTexture2DLocation  = glGetUniformLocation( program->getId()   // Getting normals 2D texture uniform location.
                                                          , Uniform::NORMALS_TEXTURE_2D
                                                          );
    GLint depthTexture2DLocation    = glGetUniformLocation( program->getId()   // Getting depth 2D texture uniform location.
                                                          , Uniform::DEPTH_TEXTURE_2D
                                                          );

    QMatrix4x4 projectionView       = renderer->getScene()->getCamera().getProjectionView();    // Getting projection view matrix.
    QMatrix4x4 model                = m_transforms.getModel();                                  // Getting model matrix.
    QMatrix4x4 invProjectionView    = projectionView.inverted();                                // Getting inverse projection view matrix.

    glUniformMatrix4fv(projectionViewLocation,    1, GL_FALSE,  projectionView.constData()    );// Specifying the value of a projection view uniform.
    glUniformMatrix4fv(modelLocation,             1, GL_FALSE,  model.constData()             );// Specifying the value of a model uniform.
    glUniformMatrix4fv(invProjectionViewLocation, 1, GL_FALSE,  invProjectionView.constData() );// Specifying the value of an inverse projection view uniform.
    glUniform4fv(lightColorLocation,              1,           &(getLightColor()[0])          );// Specifying the value of light color uniform.
    glUniform1f(lightRadiusLocation,                            m_radius                      );// Specifying the value of light radius uniform.
    glUniform3fv(lightPositionLocation,           1,           &(m_position[0])               );// Specifying the value of light position uniform.

    GLint  texturesLocations[] { normalsTexture2DLocation
                               , depthTexture2DLocation };
    GLuint texturesIds[] { renderer->getRenderTarget().getTexturesIds().value(TargetTextures::NORMALS)
                         , renderer->getRenderTarget().getTexturesIds().value(TargetTextures::DEPTH) };
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


    glDrawElements(m_mesh.getMode(), m_mesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) );  // Drawing elements.


    glDisableVertexAttribArray(Attribute::COORDINATE);  // Disabling coordinate attribute.

    for( uint j = 0; j < length; ++j )
    {
        glActiveTexture(GL_TEXTURE0 + j);   // Activating texture.
        glBindTexture(GL_TEXTURE_2D, 0);    // Unbinding texture.
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);            // Unbinding VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);    // Unbinding IBO buffer.


    program->stopUse();

}

const PointLight & PointLight::operator = (const PointLight &light)
{
    Light::operator = (light);
    m_mesh          = light.m_mesh;
    m_transforms    = light.m_transforms;
    m_radius        = light.m_radius;
    m_program       = light.m_program;   
    m_position      = light.m_position;

    return *this;
}

bool PointLight::operator == (const PointLight &light) const
{
    std::shared_ptr<Program> thisProgram    = m_program.lock();
    std::shared_ptr<Program> anotherProgram = light.m_program.lock();

    bool equal = false;

    if(  Light::operator   == (light)
      && m_mesh            == light.m_mesh
      && m_transforms      == light.m_transforms
      && m_radius          == light.m_radius
      && thisProgram.get() == anotherProgram.get()     
      && m_position        == light.m_position )
    {
        equal = true;
    }

    return equal;
}

bool PointLight::operator != (const PointLight &light) const
{
    return !(*this == light);
}

void PointLight::setMesh(const Mesh &mesh)
{
    m_mesh = mesh;
}

void PointLight::setTransforms(const Transforms &transforms)
{
    m_transforms = transforms;
}

void PointLight::setRadius(GLfloat radius)
{
    m_radius = radius;
}

void PointLight::setProgram(std::weak_ptr<Program> program)
{
    m_program = program;
}

void PointLight::setPosition(const QVector3D &position)
{
    m_position = position;
}

void PointLight::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_position.setX(x);
    m_position.setY(y);
    m_position.setZ(z);
}

std::shared_ptr<PointLight> PointLight::createObject()
{
    return std::make_shared<PointLight>();
}

PointLight::PointLight(const PointLight &light) :
    Light        ( light              ),
    m_mesh       ( light.m_mesh       ),
    m_transforms ( light.m_transforms ),
    m_radius     ( light.m_radius     ),
    m_program    ( light.m_program    ),    
    m_position   ( light.m_position   )
{
}
