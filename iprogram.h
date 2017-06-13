#ifndef IPROGRAM_H
#define IPROGRAM_H

#include "commonincludings.h"

//! Interface for OpenGL shader programs.
class IProgram
{
public:
    virtual GLuint create() noexcept(false) = 0;    //! Reads and compiles shaders, creates program and returns its id.
    virtual GLuint link() noexcept(false) = 0;      //! Links program to OpenGL context and returns its id.
    virtual GLuint use() = 0;                       //! Marks this program to be used in OpenGL scene drawing operations. Returns program id.
    virtual GLuint stopUse() = 0;                   //! Stops using this program, returns program id.
    virtual GLuint remove() = 0;                    //! Deletes program and returns its id.

    virtual ~IProgram() {}
};

#endif // IPROGRAM_H
