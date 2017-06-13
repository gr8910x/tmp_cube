#ifndef IRENDERER_H
#define IRENDERER_H

#include "commonincludings.h"

//! Interface for OpenGL renderer implementation.
class IRenderer
{
public:
    virtual GLuint genBuffers() noexcept(false) = 0;   //! Generates FBO, textures and rectangle VBO & IBO of renderer and returns FBO id.
    virtual GLuint deleteBuffers() = 0;                //! Deletes FBO, textures and rectangle VBO & IBO of renderer and returns id of deleted FBO.

    virtual void renderGBuffer() noexcept(false) = 0;  //! Renders geometry buffer.
    virtual void renderLBuffer() noexcept(false) = 0;  //! Renders light buffer.
    virtual void postProcess() noexcept(false) = 0;    //! Provides post processing.
    virtual void finalRender() noexcept(false) = 0;    //! Provides rendering to screen buffer.

    virtual ~IRenderer() {}
};

#endif // IRENDERER_H
