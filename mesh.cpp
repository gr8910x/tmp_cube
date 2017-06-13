#include "mesh.h"
#include "meshexception.h"

using namespace com_defs;

GLuint Mesh::counter = 0;

Mesh::Mesh() :
    m_vertices    (                                    ),
    m_indices     (                                    ),
    m_vbo         (                                    ),
    m_ibo         (                                    ),
    m_vboId       (  0                                 ),
    m_iboId       (  0                                 ),
    m_mode        (  GL_TRIANGLES                      ),
    m_description (  "Empty description"               ),
    m_status      (  MeshStatus::BUFFERS_NOT_GENERATED
                   | MeshStatus::NO_IBO_DATA
                   | MeshStatus::NO_VBO_DATA           )
{
    m_name = ++ Mesh::counter;
}

Mesh::Mesh( const QVector<Vertex> &vertices
          , const QVector<Index>  &indices
          ) :
    m_vertices    ( vertices                          ),
    m_indices     ( indices                           ),
    m_vbo         (                                   ),
    m_ibo         (                                   ),
    m_vboId       ( 0                                 ),
    m_iboId       ( 0                                 ),
    m_mode        ( GL_TRIANGLES                      ),
    m_description ( "Empty description"               ),
    m_status      ( MeshStatus::BUFFERS_NOT_GENERATED )
{
    m_name = ++ Mesh::counter;    
    fill();
}

Mesh::Mesh( const QVector<Vertex> &vertices
          , const QVector<Index>  &indices
          , GLenum                 mode
          ) :
    m_vertices    ( vertices                          ),
    m_indices     ( indices                           ),
    m_vbo         (                                   ),
    m_ibo         (                                   ),
    m_vboId       ( 0                                 ),
    m_iboId       ( 0                                 ),
    m_mode        ( mode                              ),
    m_description ( "Empty description"               ),
    m_status      ( MeshStatus::BUFFERS_NOT_GENERATED )
{
    m_name = ++ Mesh::counter;   
    fill();
}

Mesh::Mesh( const QVector<Vertex> &vertices
          , const QVector<Index>  &indices
          , GLenum                 mode
          , const QString         &description
          ) :
    m_vertices    ( vertices                          ),
    m_indices     ( indices                           ),
    m_vbo         (                                   ),
    m_ibo         (                                   ),
    m_vboId       ( 0                                 ),
    m_iboId       ( 0                                 ),
    m_mode        ( mode                              ),
    m_description ( description                       ),
    m_status      ( MeshStatus::BUFFERS_NOT_GENERATED )
{
    m_name = ++ Mesh::counter;    
    fill();
}

Mesh::Mesh( const Mesh &mesh ) :
    m_vertices    ( mesh.m_vertices    ),
    m_indices     ( mesh.m_indices     ),
    m_vbo         ( mesh.m_vbo         ),
    m_ibo         ( mesh.m_ibo         ),
    m_vboId       ( mesh.m_vboId       ),
    m_iboId       ( mesh.m_iboId       ),
    m_mode        ( mesh.m_mode        ),
    m_name        ( mesh.m_name        ),
    m_description ( mesh.m_description ),
    m_status      ( mesh.m_status      )
{    
}

void Mesh::fill()
{
    fillVBO();
    fillIBO();
}

const Mesh & Mesh::operator = (const Mesh &mesh)
{    
    m_vertices.resize(mesh.m_vertices.length() );
    m_indices.resize(mesh.m_indices.length() );
    uint i = 0;
    for( Vertex &vertex: m_vertices )
    {
        vertex = mesh.m_vertices[i];        // Assigning vertices.
        ++i;
    }
    i = 0;
    for( Index &index: m_indices )
    {
        index = mesh.m_indices[i];          // Assigning indices.
        ++i;
    }
    m_mode          = mesh.m_mode;
    m_description   = mesh.m_description;

    fill();

    return *this;
}

bool Mesh::operator == (const Mesh &mesh) const
{
    bool equal = false;

    if(  m_vertices    == mesh.m_vertices
      && m_indices     == mesh.m_indices
      && m_vbo         == mesh.m_vbo
      && m_ibo         == mesh.m_ibo
      && m_mode        == mesh.m_mode )
    {
        equal = true;
    }

    return equal;
}

bool Mesh::operator != (const Mesh &mesh) const
{
    return !(*this == mesh);
}

void Mesh::setVertices(const QVector<Vertex> &vertices)
{
    m_vertices = vertices;
    fillVBO();
}

void Mesh::setIndices(const QVector<Index> &indices)
{
    m_indices = indices;
    fillIBO();
}

void Mesh::setDescription(const QString &description)
{
    m_description = description;
}

bool Mesh::isGenerated() const
{
    return (m_status & MeshStatus::BUFFERS_NOT_GENERATED) != MeshStatus::BUFFERS_NOT_GENERATED;
}

QPair<GLuint, GLuint> Mesh::genBuffers()
{    
    if( (m_status & MeshStatus::BUFFERS_NOT_GENERATED) == MeshStatus::BUFFERS_NOT_GENERATED )// Checking if buffers were not generated.
    {
        GLuint buffersIds[NUM_OF_BUFFERS_PER_MESH] = { 0, 0 };
        glGenBuffers(NUM_OF_BUFFERS_PER_MESH, &(buffersIds[0]) );

        m_vboId = buffersIds[0];
        m_iboId = buffersIds[1];

        m_status &= ~MeshStatus::BUFFERS_NOT_GENERATED;     // Disabling BUFFERS_NOT_GENERATED flag.
    }

    return QPair<GLuint, GLuint>(m_vboId, m_iboId);
}

QPair<GLuint, GLuint> Mesh::deleteBuffers()
{
    QPair<GLuint, GLuint> deletedBuffersIds(0, 0);    
    if( (m_status & MeshStatus::BUFFERS_NOT_GENERATED) != MeshStatus::BUFFERS_NOT_GENERATED )// Checking if buffers were generated.
    {
        const GLuint buffersIds[NUM_OF_BUFFERS_PER_MESH] = { m_vboId, m_iboId };
        glDeleteBuffers(NUM_OF_BUFFERS_PER_MESH, &(buffersIds[0]) );

        deletedBuffersIds.first  = m_vboId;
        deletedBuffersIds.second = m_iboId;

        m_vboId = 0;
        m_iboId = 0;

        m_status |= MeshStatus::BUFFERS_NOT_GENERATED;      // Enabling BUFFERS_NOT_GENERATED flag.
    }

    return deletedBuffersIds;
}

QPair<GLuint, GLuint> Mesh::pushData() noexcept(false)
{
    QPair<GLuint, GLuint> buffersIds(0, 0);
    if( m_status != MeshStatus::FINE )                                       // Checking if VBO or IBO buffers were not generated.
    {
        throw MeshException(this, "Mesh exception occured");
    }
    else
    {
        GLsizeiptr coordinatesSize =  m_vertices.length()                    // Size of coordinates in bytes in VBO buffer.
                                    * NUM_OF_COORDINATE_COMPONENTS_PER_VERTEX
                                    * sizeof(GLfloat);
        GLsizeiptr colorsSize      =  m_vertices.length()                    // Size of colors in bytes in VBO buffer.
                                    * NUM_OF_COLOR_COMPONENTS_PER_VERTEX
                                    * sizeof(GLfloat);
        GLsizeiptr normalsSize     =  m_vertices.length()                    // Size of normals in bytes in VBO buffer.
                                    * NUM_OF_NORMAL_COMPONENTS_PER_VERTEX
                                    * sizeof(GLfloat);
        GLsizeiptr totalVBOSize    =  coordinatesSize                        // Total size in bytes of VBO buffer.
                                    + colorsSize
                                    + normalsSize;

        GLsizeiptr totalIBOSize    =  m_indices.length()                     // Total size in bytes of IBO buffer.
                                    * sizeof(GLuint);


        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);                              // Binding VBO buffer.
        glBufferData(GL_ARRAY_BUFFER, totalVBOSize, NULL, GL_STATIC_DRAW);
        GLfloat *vboBuffer = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        ( !vboBuffer ) ? m_status |=  MeshStatus::INVALID_VBO_BUFFER_POINTER // Changing status.
                       : m_status &= ~MeshStatus::INVALID_VBO_BUFFER_POINTER;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);                      // Binding IBO buffer.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIBOSize, NULL, GL_STATIC_DRAW);
        GLuint  *iboBuffer = (GLuint *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        ( !iboBuffer ) ? m_status |=  MeshStatus::INVALID_IBO_BUFFER_POINTER // Changing status.
                       : m_status &= ~MeshStatus::INVALID_IBO_BUFFER_POINTER;
        if( m_status != MeshStatus::FINE )
        {
            throw MeshException(this, "Mesh exception occured");
        }


        memcpy(vboBuffer, m_vbo.constData(), totalVBOSize);                  // Pushing VBO data to OpenGL.
        memcpy(iboBuffer, m_ibo.constData(), totalIBOSize);                  // Pushing IBO data to OpenGL.


        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        bool vboBufferUnmapped = glUnmapBuffer(GL_ARRAY_BUFFER);             // Unmapping VBO buffer.
        ( !vboBufferUnmapped ) ? m_status |=  MeshStatus::INVALID_VBO_UNMAPPING // Changing status.
                               : m_status &= ~MeshStatus::INVALID_VBO_UNMAPPING;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
        bool iboBufferUnmapped = glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);     // Unmapping IBO buffer.
        ( !iboBufferUnmapped ) ? m_status |=  MeshStatus::INVALID_IBO_UNMAPPING // Changing status.
                               : m_status &= ~MeshStatus::INVALID_IBO_UNMAPPING;
        if( m_status != MeshStatus::FINE )
        {
            throw MeshException(this, "Mesh exception occured");
        }


        glBindBuffer(GL_ARRAY_BUFFER, 0);                                    // Unbinding VBO buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                            // Unbinding IBO buffer.


        buffersIds.first  = m_vboId;
        buffersIds.second = m_iboId;
    }

    return buffersIds;
}

void Mesh::fillVBO()
{
    m_vbo.clear();
    m_vbo.resize(NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * m_vertices.length() );

    QVector<QVector3D> normals(m_vertices.length() );
    uint i = 0;
    for( QVector<Vertex>::const_iterator it = m_vertices.constBegin(); it != m_vertices.constEnd(); ++it )
    //for( const Vertex& vertex : m_vertices)
    {
        normals[i] = it->getNormal();
        ++i;
    }
    aux_funcs::normalize(normals);

    i = 0;
    for( QVector<Vertex>::const_iterator it = m_vertices.constBegin(); it != m_vertices.constEnd(); ++it )
    {
        uint j = 0;

        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getCoordinates().x();   // Filling coordinates.
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getCoordinates().y();
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getCoordinates().z();

        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getColor().x();         // Filling colors.
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getColor().y();
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getColor().z();
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = it->getColor().w();

        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = normals[i].x();             // Filling normals.
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = normals[i].y();
        m_vbo[NUM_OF_TOTAL_COMPONENTS_PER_VERTEX * i + j++]   = normals[i].z();

        ++i;
    }    
    ( m_vbo.empty() ) ? m_status |=  MeshStatus::NO_VBO_DATA                                // Setting status.
                      : m_status &= ~MeshStatus::NO_VBO_DATA;
}

void Mesh::fillIBO()
{
    m_ibo.clear();
    m_ibo.resize(m_indices.length() );

    uint i = 0;
    for( QVector<Index>::const_iterator it = m_indices.constBegin(); it != m_indices.constEnd(); ++it )
    {
        m_ibo[i] = it->getIndex();                                                          // Filling indices.
        ++i;
    }
    ( m_ibo.empty() ) ? m_status |=  MeshStatus::NO_IBO_DATA                                // Setting status.
                      : m_status &= ~MeshStatus::NO_IBO_DATA;
}
