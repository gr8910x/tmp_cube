#ifndef MESH_H
#define MESH_H

#include "commonincludings.h"
#include "imesh.h"
#include "vertex.h"
#include "index.h"

//! Implements OpenGL mesh which contains vertices and VBO, indices and IBO.
class Mesh : public IMesh
{
public:
    Mesh();                                                           //! Default constructor.
    Mesh( const QVector<Vertex> &vertices                             //! Parameterized constructor.
        , const QVector<Index>  &indices
        );
    Mesh( const QVector<Vertex> &vertices                             //! Parameterized constructor.
        , const QVector<Index>  &indices
        , GLenum                 mode
        );
    Mesh( const QVector<Vertex> &vertices                             //! Parameterized constructor.
        , const QVector<Index>  &indices
        , GLenum                 mode
        , const QString         &description
        );

    Mesh( const Mesh &mesh );                                         //! Copying constructor.

    virtual ~Mesh() {}

    virtual QPair<GLuint, GLuint> genBuffers() override;              //! Generates VBO & IBO buffers and returns their ids in QPair, where QPair::first is VBO id and QPair::second is IBO id.
    virtual QPair<GLuint, GLuint> deleteBuffers() override;           //! Deletes VBO & IBO mesh buffers from OpenGL context and returns ids of deleted buffers, where QPair::first is VBO id and QPair::second is IBO id. Returns { 0, 0 } if no buffers were deleted.
    virtual QPair<GLuint, GLuint> pushData() noexcept(false) override;//! Pushes data from VBO & IBO vectors to corresponding OpenGL VBO & IBO buffers. Returns ids of buffers where new data was copied, where QPair::first is VBO id and QPair::second is IBO id. Returns { 0, 0 } if no data was copied.

    void fill();                                                      //! Refills VBO and IBO vectors with data from vertices and indices vectors respectively.
    void fillVBO();                                                   //! Fills VBO vector with data from vertices.
    void fillIBO();                                                   //! Fills IBO vector with data from indices.

    const Mesh & operator = (const Mesh &mesh);                       //! Operator " =  ".
    bool  operator == (const Mesh &mesh) const;                       //! Operator " == ".
    bool  operator != (const Mesh &mesh) const;                       //! Operator " != ".

public:
    const QVector<Vertex> & getVertices() const { return m_vertices; }//! Returns vector of mesh vertices.
    const QVector<Index>  & getIndices()  const { return m_indices; } //! Returns vector of mesh indices.
    QVector<Vertex> & getVertices() { return m_vertices; }            //! Returns vector of mesh vertices, overloaded function.
    QVector<Index>  & getIndices()  { return m_indices; }             //! Returns vector of mesh indices, overloaded function.
    void setVertices(const QVector<Vertex> &vertices);                //! Sets vector of mesh vertices.
    void setIndices(const QVector<Index> &indices);                   //! Sets vector of mesh indices.

    const QVector<GLfloat> & getVBO() const { return m_vbo; }         //! Returns vector of mesh VBO components.
    const QVector<GLuint>  & getIBO() const { return m_ibo; }         //! Returns vector of mesh IBO components.
    QVector<GLfloat> & getVBO() { return m_vbo; }                     //! Returns vector of mesh VBO components, overloaded function.
    QVector<GLuint>  & getIBO() { return m_ibo; }                     //! Returns vector of mesh IBO components, overloaded function.

    GLuint getVBOId() const { return m_vboId; }                       //! Returns generated by OpenGL id of mesh VBO.
    GLuint getIBOId() const { return m_iboId; }                       //! Returns generated by OpenGL id of mesh IBO.

    GLenum getMode() const { return m_mode; }                         //! Returns OpenGL painting mode.
    void   setMode(GLenum mode) { m_mode = mode; }                    //! Sets OpenGL painting mode.

    GLuint getName() const { return m_name; }                         //! Returns autogenerated name of mesh.

    const QString & getDescription() const { return m_description; }  //! Returns description of mesh.
    void  setDescription(const QString &description);                 //! Sets description of mesh.

    bool  isGenerated() const;                                        //! Returns true if VBO & IBO buffers were generated

    uint getStatus() const { return m_status; }                       //! Returns mesh object status bitmask.

public:
    static GLuint   getCounter() { return counter; }                  //! Returns number of created meshes.

protected:
    void setVBOId(uint vboId)   { m_vboId = vboId; }                  //! Sets generated by OpenGL id of mesh VBO.
    void setIBOId(uint iboId)   { m_iboId = iboId; }                  //! Sets generated by OpneGL id of mesh IBO.
    void setStatus(uint status) { m_status = status; }                //! Sets mesh object status bitmask.

private:
    static GLuint   counter;              //! Counter of created meshes.

private:
    QVector<Vertex>      m_vertices;      //! Vector of mesh vertices.
    QVector<Index>       m_indices;       //! Vector of mesh indices.

    QVector<GLfloat>     m_vbo;           //! Vector of mesh VBO components.
    QVector<GLuint>      m_ibo;           //! Vector of mesh IBO components.

    GLuint               m_vboId;         //! Generated by OpenGL id of mesh VBO, 0 by default.
    GLuint               m_iboId;         //! Generated by OpneGL id of mesh IBO, 0 by default.

    GLenum               m_mode;          //! OpenGL painting mode, GL_TRIANGLES by default.

    GLuint               m_name;          //! Autogenerated name of mesh.

    QString              m_description;   //! Description of mesh.    

    uint                 m_status;        //! Mesh object status bitmask.
};

#endif // MESH_H
