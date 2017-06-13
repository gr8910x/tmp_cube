#ifndef IMESH_H
#define IMESH_H

#include "commonincludings.h"

//! Interface for OpenGL mesh implementation.
class IMesh
{
public:
    virtual QPair<GLuint, GLuint> genBuffers() = 0;              //! Generates VBO & IBO buffers and returns their ids in QPair, where QPair::first is VBO id and QPair::second is IBO id.
    virtual QPair<GLuint, GLuint> deleteBuffers() = 0;           //! Deletes VBO & IBO mesh buffers from OpenGL context and returns ids of deleted buffers, where QPair::first is VBO id and QPair::second is IBO id. Returns { 0, 0 } if buffers being deleting was not even generated.
    virtual QPair<GLuint, GLuint> pushData() noexcept(false) = 0;//! Pushes data from VBO & IBO vectors to corresponding OpenGL VBO & IBO buffers. Returns ids of buffers where new data was copied, where QPair::first is VBO id and QPair::second is IBO id. Returns { 0, 0 } if no data was copied.

    virtual ~IMesh() {}

};

#endif // IMESH_H
