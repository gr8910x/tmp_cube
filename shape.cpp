#include "shape.h"
#include "shapeexception.h"
#include "program.h"
#include "camera.h"
#include "texture.h"

using namespace com_defs;

GLuint Shape::counter = 0;

Shape::Shape() :
    m_mesh        (                     ),
    m_transforms  (                     ),
    m_program     (                     ),
    m_textures    (                     ),
    m_description ( "Empty description" ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const Mesh &mesh ) :
    m_mesh        ( mesh                ),
    m_transforms  (                     ),
    m_program     (                     ),
    m_textures    (                     ),
    m_description ( "Empty description" ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const Transforms &transforms ) :
    m_mesh        (                     ),
    m_transforms  ( transforms          ),
    m_program     (                     ),
    m_textures    (                     ),
    m_description ( "Empty description" ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( std::weak_ptr<Program> program ) :
    m_mesh        (                     ),
    m_transforms  (                     ),
    m_program     ( program             ),
    m_textures    (                     ),
    m_description ( "Empty description" ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const QString &description ) :
    m_mesh        (                   ),
    m_transforms  (                   ),
    m_program     (                   ),
    m_textures    (                   ),
    m_description ( description       ),
    m_status      ( ShapeStatus::FINE )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const Mesh       &mesh
            , const Transforms &transforms ) :
    m_mesh        ( mesh                ),
    m_transforms  ( transforms          ),
    m_program     (                     ),
    m_textures    (                     ),
    m_description ( "Empty description" ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const Mesh             &mesh
            , const Transforms       &transforms
            , std::weak_ptr<Program>  program ) :
    m_mesh         ( mesh                ),
    m_transforms   ( transforms          ),
    m_program      ( program             ),
    m_textures     (                     ),
    m_description  ( "Empty description" ),
    m_status       ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const Mesh             &mesh
            , const Transforms       &transforms
            , std::weak_ptr<Program>  program
            , const QString          &description ) :
    m_mesh        ( mesh                ),
    m_transforms  ( transforms          ),
    m_program     ( program             ),
    m_textures    (                     ),
    m_description ( description         ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const Mesh             &mesh
            , const Transforms       &transforms
            , std::weak_ptr<Program>  program
            , const QHash<QString, std::weak_ptr<Texture> > &textures
            , const QString          &description ) :
    m_mesh        ( mesh                ),
    m_transforms  ( transforms          ),
    m_program     ( program             ),
    m_textures    ( textures            ),
    m_description ( description         ),
    m_status      ( ShapeStatus::FINE   )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const QVector<Vertex>  &vertices
            , const QVector<Index>   &indices
            , GLenum                  mode
            , const QString          &meshDescription
            , const Transforms       &transforms
            , std::weak_ptr<Program>  program
            , const QHash<QString, std::weak_ptr<Texture> > &textures
            , const QString          &shapeDescription ) :
    m_mesh        ( vertices, indices, mode, meshDescription ),
    m_transforms  ( transforms                               ),
    m_program     ( program                                  ),
    m_textures    ( textures                                 ),
    m_description ( shapeDescription                         ),
    m_status      ( ShapeStatus::FINE                        )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const QVector<Vertex>  &vertices
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
            , const QString          &shapeDescription ) :
    m_mesh          ( vertices,      indices,      mode,         meshDescription ),
    m_transforms    ( translationX,  translationY, translationZ,
                      rotationAngle, rotationX,    rotationY,    rotationZ,
                      scalingX,      scalingY,     scalingZ                      ),
    m_program       ( program                                                    ),
    m_textures      (                                                            ),
    m_description   ( shapeDescription                                           ),
    m_status        ( ShapeStatus::FINE                                          )
{
    m_name = ++ Shape::counter;
}

Shape::Shape( const QVector<Vertex> &vertices
            , const QVector<Index>  &indices
            , GLenum                 mode
            , const QString         &meshDescription
            , GLfloat                translationX
            , GLfloat                translationY
            , GLfloat                translationZ
            , GLfloat                rotationAngle
            , GLfloat                rotationX
            , GLfloat                rotationY
            , GLfloat                rotationZ
            , GLfloat                scalingX
            , GLfloat                scalingY
            , GLfloat                scalingZ
            , std::weak_ptr<Program> program
            , const QHash<QString, std::weak_ptr<Texture> > &textures
            , const QString         &shapeDescription ) :
    m_mesh          ( vertices,      indices,      mode,         meshDescription ),
    m_transforms    ( translationX,  translationY, translationZ,
                      rotationAngle, rotationX,    rotationY,    rotationZ,
                      scalingX,      scalingY,     scalingZ                      ),
    m_program       ( program                                                    ),
    m_textures      ( textures                                                   ),
    m_description   ( shapeDescription                                           ),
    m_status        ( ShapeStatus::FINE                                          )
{
    m_name = ++ Shape::counter;
}

Shape::~Shape()
{
    m_mesh.deleteBuffers();
}

void Shape::draw(const Camera *camera) noexcept(false)
{
    static GLuint attempts = 0;

    GLboolean vboIsFine = glIsBuffer(m_mesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(m_mesh.getIBOId() );
    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? m_status |=  ShapeStatus::INVALID_BUFFERS
                                                       : m_status &= ~ShapeStatus::INVALID_BUFFERS;

    if( (m_status & ShapeStatus::INVALID_BUFFERS) == ShapeStatus::INVALID_BUFFERS ) // Checking shape buffers.
    {
        ++ attempts;
        m_mesh.deleteBuffers();                         // Refilling VBO and IBO data.
        m_mesh.genBuffers();
        m_mesh.fill();
        m_mesh.pushData();
        draw(camera);                                   // Trying to draw a shape NUM_OF_SHAPE_DRAW_ATTEMPTS times.
        if( attempts > NUM_OF_SHAPE_DRAW_ATTEMPTS )     // Attempts limit depleted.
        {
            attempts = 0;
            throw ShapeException(this, "Shape exception occured");
        }
        return;
    }
    else
    {
        attempts = 0;
    }

    std::shared_ptr<Program> program = m_program.lock();
    ( !program ) ? m_status |=  ShapeStatus::NO_PROGRAM
                 : m_status &= ~ShapeStatus::NO_PROGRAM;

    if( (m_status & ShapeStatus::NO_PROGRAM) == ShapeStatus::NO_PROGRAM ) // Checking if program is set.
    {
        throw ShapeException(this, "Shape exception occured");
    }

    program->use();                 // Using shading program.

    glBindBuffer(GL_ARRAY_BUFFER, m_mesh.getVBOId() );// Binding VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);
    GLsizei colorsStride      =   coordinatesStride;
    GLsizei normalsStride     =   coordinatesStride;

    GLsizei coordinatesShift  =   0;
    GLsizei colorsShift       =   NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                                * sizeof(GLfloat);
    GLsizei normalsShift      = ( NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                                + NUM_OF_COLOR_COMPONENTS_PER_VERTEX )
                                * sizeof(GLfloat);

    glEnableVertexAttribArray(Attribute::COORDINATE);       // Enabling coordinate attribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );
    glEnableVertexAttribArray(Attribute::COLOR);            // Enabling color attribute
    glVertexAttribPointer( Attribute::COLOR
                         , NUM_OF_COLOR_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , colorsStride
                         , BUFFER_OFFSET(colorsShift)
                         );
    glEnableVertexAttribArray(Attribute::NORMAL);           // Enabling normal attribute.
    glVertexAttribPointer( Attribute::NORMAL
                         , NUM_OF_NORMAL_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , normalsStride
                         , BUFFER_OFFSET(normalsShift)
                         );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBOId() );// Binding IBO buffer.

    GLint projectionViewModelLocation = glGetUniformLocation( program->getId()   // Getting projection view model matrix uniform location.
                                                            , Uniform::PROJECTION_VIEW_MODEL
                                                            );
    GLint modelLocation               = glGetUniformLocation( program->getId()   // Getting model matrix uniform location.
                                                            , Uniform::MODEL
                                                            );
    QMatrix4x4 view                = camera->getView();         // Getting view matrix.
    QMatrix4x4 projection          = camera->getProjection();   // Getting projection matrix.
    QMatrix4x4 model               = m_transforms.getModel();   // Getting model matrix.
    QMatrix4x4 projectionViewModel = projection * view * model; // Calculating projection view model matrix.
    glUniformMatrix4fv(projectionViewModelLocation, 1, GL_FALSE, projectionViewModel.constData() );// Specifying the value of a projection view model uniform.
    glUniformMatrix4fv(modelLocation,               1, GL_FALSE, model.constData()               );// Specifying the value of a model uniform.


    glDrawElements(m_mesh.getMode(), m_mesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) );  // Drawing elements.


    glDisableVertexAttribArray(Attribute::COORDINATE);      // Disabling coordinate attribute.
    glDisableVertexAttribArray(Attribute::COLOR);           // Disabling color attribute.
    glDisableVertexAttribArray(Attribute::NORMAL);          // Disabling normal attribute.

    glBindBuffer(GL_ARRAY_BUFFER, 0);                       // Unbinding VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);               // Unbinding IBO buffer.


    program->stopUse();                 // Stop using shading program.


    program.reset();
}

void Shape::drawShadow(const Camera *camera) noexcept(false)
{
    static GLuint attempts = 0;

    GLboolean vboIsFine = glIsBuffer(m_mesh.getVBOId() );
    GLboolean iboIsFine = glIsBuffer(m_mesh.getIBOId() );
    ( vboIsFine == GL_FALSE || iboIsFine == GL_FALSE ) ? m_status |=  ShapeStatus::INVALID_BUFFERS
                                                       : m_status &= ~ShapeStatus::INVALID_BUFFERS;

    if( (m_status & ShapeStatus::INVALID_BUFFERS) == ShapeStatus::INVALID_BUFFERS ) // Checking shape buffers.
    {
        ++ attempts;
        m_mesh.deleteBuffers();                         // Refilling VBO and IBO data.
        m_mesh.genBuffers();
        m_mesh.fill();
        m_mesh.pushData();
        draw(camera);                                   // Trying to draw a shape NUM_OF_SHAPE_DRAW_ATTEMPTS times.
        if( attempts > NUM_OF_SHAPE_DRAW_ATTEMPTS )     // Attempts limit depleted.
        {
            attempts = 0;
            throw ShapeException(this, "Shape exception occured");
        }
        return;
    }
    else
    {
        attempts = 0;
    }


    std::shared_ptr<Program> program = m_shadowProgram.lock();
    ( !program ) ? m_status |=  ShapeStatus::NO_PROGRAM
                 : m_status &= ~ShapeStatus::NO_PROGRAM;

    if( (m_status & ShapeStatus::NO_PROGRAM) == ShapeStatus::NO_PROGRAM ) // Checking if program is set.
    {
        throw ShapeException(this, "Shape exception occured");
    }

    program->use();                 // Using shadow program.

    glBindBuffer(GL_ARRAY_BUFFER, m_mesh.getVBOId() );// Binding VBO buffer.
    GLsizei coordinatesStride =   NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * sizeof(GLfloat);
    GLsizei coordinatesShift  =   0;

    glEnableVertexAttribArray(Attribute::COORDINATE);       // Enabling coordinate attribute.
    glVertexAttribPointer( Attribute::COORDINATE
                         , NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                         , GL_FLOAT
                         , GL_FALSE
                         , coordinatesStride
                         , BUFFER_OFFSET(coordinatesShift)
                         );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBOId() );// Binding IBO buffer.

    GLint projectionViewModelLocation = glGetUniformLocation( program->getId()   // Getting projection view model matrix uniform location.
                                                            , Uniform::PROJECTION_VIEW_MODEL
                                                            );

    QMatrix4x4 view                = camera->getView();         // Getting view matrix.
    QMatrix4x4 projection          = camera->getProjection();   // Getting projection matrix.
    QMatrix4x4 model               = m_transforms.getModel();   // Getting model matrix.
    QMatrix4x4 projectionViewModel = projection * view * model; // Calculating projection view model matrix.
    glUniformMatrix4fv(projectionViewModelLocation, 1, GL_FALSE, projectionViewModel.constData() );// Specifying the value of a projection view model uniform.


    glDrawElements(m_mesh.getMode(), m_mesh.getIBO().length(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) );  // Drawing elements.


    glDisableVertexAttribArray(Attribute::COORDINATE);      // Disabling coordinate attribute.
    glBindBuffer(GL_ARRAY_BUFFER, 0);                       // Unbinding VBO buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);               // Unbinding IBO buffer.


    program->stopUse();                 // Stop using shadow program.
}

const Shape & Shape::operator = (const Shape &shape)
{
    m_mesh        = shape.m_mesh;
    m_transforms  = shape.m_transforms;
    m_program     = shape.m_program;
    m_shadowProgram = shape.m_shadowProgram;
    m_textures    = shape.m_textures;
    m_description = shape.m_description;

    return *this;
}

bool Shape::operator == (const Shape &shape) const
{
    bool equal = false;

    QList<std::shared_ptr<const Texture> > theseTextures, otherTextures;
    for(  QHash<QString, std::weak_ptr<Texture> >::const_iterator it = m_textures.constBegin(); it != m_textures.constEnd(); ++it )
    {
        theseTextures << it.value().lock();
    }
    for(  QHash<QString, std::weak_ptr<Texture> >::const_iterator it = shape.m_textures.constBegin(); it != shape.m_textures.constEnd(); ++it )
    {
        otherTextures << it.value().lock();
    }

    bool texturesEqual = false;
    if( theseTextures.length() == otherTextures.length() )
    {
        texturesEqual = true;
        for( int i = 0; i < theseTextures.length(); ++i )
        {
            if( theseTextures[i].get() != otherTextures[i].get() )
            {
                texturesEqual = false;
                break;
            }
        }
    }

    std::shared_ptr<const Program> thisProgram    = m_program.lock();
    std::shared_ptr<const Program> anotherProgram = shape.m_program.lock();

    if(  m_mesh            ==  shape.m_mesh
      && m_transforms      ==  shape.m_transforms
      && thisProgram.get() ==  anotherProgram.get()
      && texturesEqual
      )
    {
        equal = true;
    }    

    return equal;
}

bool Shape::operator != (const Shape &shape) const
{
    return !(*this == shape);
}

void Shape::setMesh(const Mesh &mesh)
{
    m_mesh = mesh;
}

void Shape::setTransforms(const Transforms &transforms)
{
    m_transforms = transforms;
}

void Shape::setProgram(std::weak_ptr<Program> program)
{
    m_program = program;
}

void Shape::setShadowProgram(std::weak_ptr<Program> shadowProgram)
{
    m_shadowProgram = shadowProgram;
}

void Shape::setTextures(const QHash<QString, std::weak_ptr<Texture> > &textures)
{
    m_textures = textures;
}

void Shape::setDescription(const QString &description)
{
    m_description = description;
}

std::shared_ptr<Shape> Shape::createObject()
{
    return std::make_shared<Shape>();
}

Shape::Shape( const Shape &shape ) :
    m_mesh         ( shape.m_mesh          ),
    m_transforms   ( shape.m_transforms    ),
    m_program      ( shape.m_program       ),
    m_shadowProgram( shape.m_shadowProgram ),
    m_textures     ( shape.m_textures      ),
    m_name         ( shape.m_name          ),
    m_description  ( shape.m_description   ),
    m_status       ( shape.m_status        )
{
}
